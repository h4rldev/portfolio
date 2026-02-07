<script lang="ts">
  import "../app.css";

  import { browser } from "$app/environment";
  import { page } from "$app/state";
  import Footer from "$components/Footer.svelte";
  import Header from "$components/Header.svelte";
  import SlideWrapper from "$components/SlideWrapper.svelte";
  import favicon from "$lib/assets/favicon.svg";

  const { children } = $props();

  let slide_direction = $state("none");
  let is_animating = $state(false);
  let touch_start = $state({ x: 0, y: 0 });
  let key_sequence: string[] = $state([]);
  let konami_ready = $state(false);
  let konami_activated = $state(false);

  let show_b_overlay = $state(false);
  let show_a_overlay = $state(false);
  const konami_code = [
    "up",
    "up",
    "down",
    "down",
    "left",
    "right",
    "left",
    "right",
    "b",
    "a",
    "enter",
  ];

  const run_oneko = async () => {
    if (browser) {
      const { oneko } = await import("$lib/oneko");

      oneko();
    }
  };

  const arrays_equal = (a: string[], b: string[]): boolean => {
    return a.length === b.length && a.every((val, index) => val === b[index]);
  };

  const reset_sequence = (): void => {
    key_sequence = [];
    konami_ready = false;
  };

  function activate_konami() {
    konami_activated = true;
    console.log("🎮🎮🎮 FULL KONAMI CODE ACTIVATED! (with Enter as Start)");

    // Do something epic here!

    setTimeout(() => {
      konami_activated = false;
      reset_sequence();
    }, 3000);
  }

  const handle_navigation = (event: KeyboardEvent) => {
    if (is_animating) return;

    is_animating = true;

    const key_map = {
      ArrowUp: "up",
      ArrowDown: "down",
      ArrowLeft: "left",
      ArrowRight: "right",
      KeyB: "b",
      KeyA: "a",
      Enter: "enter",
      Escape: "esc",
    };

    if (
      ["Shift", "Control", "Alt", "Meta", "CapsLock", "Tab"].includes(event.key)
    ) {
      reset_sequence();
      return;
    }

    const code = event.code;
    const key = code in key_map ? key_map[code as keyof typeof key_map] : null;
    if (!key) return;

    if (key === "esc") {
      slide_direction = "none";
      is_animating = false;
      reset_sequence();
      return;
    }

    if (key !== "b" && key !== "a" && key !== "enter" && key !== "esc") {
      slide_direction = key;
    }

    key_sequence = [...key_sequence, key];

    if (key_sequence.length === 8) {
      if (
        arrays_equal(key_sequence.slice(-8), [
          "up",
          "up",
          "down",
          "down",
          "left",
          "right",
          "left",
          "right",
        ])
      ) {
        konami_ready = true;
      } else {
        reset_sequence();
      }
    }

    if (
      konami_ready &&
      key === "b" &&
      key_sequence[key_sequence.length - 2] !== "b"
    ) {
      show_b_overlay = true;
      setTimeout(() => {
        show_b_overlay = false;
      }, 1500);
    }

    if (
      konami_ready &&
      key === "a" &&
      key_sequence[key_sequence.length - 2] !== "a"
    ) {
      show_a_overlay = true;
      setTimeout(() => {
        show_a_overlay = false;
      }, 1500);
    }

    if (key_sequence.length === 11) {
      const last_eleven = key_sequence.slice(-11);

      if (arrays_equal(last_eleven, konami_code)) {
        activate_konami();
        return;
      }
    }

    if (key_sequence.length > 11) {
      reset_sequence();
      slide_direction = "none";
      is_animating = false;
      return;
    }

    // Reset after animation
    setTimeout(() => {
      slide_direction = "none";
      is_animating = false;
    }, 100);
  };

  const handle_touch_start = (event: TouchEvent) => {
    touch_start.x = event.touches[0].clientX;
    touch_start.y = event.touches[0].clientY;
  };

  const handle_touch_end = (event: TouchEvent) => {
    const touch_end = {
      x: event.changedTouches[0].clientX,
      y: event.changedTouches[0].clientY,
    };

    const diffx = touch_start.x - touch_end.x;
    const diffy = touch_start.y - touch_end.y;

    // Only trigger if significant swipe
    if (Math.abs(diffx) > 50 || Math.abs(diffy) > 50) {
      const key =
        Math.abs(diffx) > Math.abs(diffy)
          ? diffx > 0
            ? "ArrowLeft"
            : "ArrowRight"
          : diffy > 0
            ? "ArrowUp"
            : "ArrowDown";

      handle_navigation(new KeyboardEvent("keyup", { key }));
    }
  };

  // Event listener
  $effect(() => {
    const handler = (event: KeyboardEvent) => handle_navigation(event);
    window.addEventListener("keyup", handler);

    return () => window.removeEventListener("keyup", handler);
  });

  run_oneko();
</script>

<svelte:head>
  <link rel="icon" href={favicon} />
</svelte:head>

<SlideWrapper direction={slide_direction}>
  <div
    ontouchstart={handle_touch_start}
    ontouchend={handle_touch_end}
  >
    <header>
      <Header />
    </header>
    <main>
      {@render children?.()}
    </main>
    <footer>
      <Footer />
    </footer>
  </div>
</SlideWrapper>

<style>
  @reference 'appcss';

  header {
    @apply w-[100vw];
  }

  main {
    @apply flex flex-col justify-center items-center mt-10 mb-6 py-4;
    @apply bg-shadow-grey-dark;
  }

  header {
    @apply max-w-[100vw];
    @apply px-0;
    @apply mx-0;
  }


  :global(main) :global(*) {
    @apply max-w-[800px];
  }

  :global(html) {
    @apply font-arimo;
  }

  :global(body) {
    @apply bg-shadow-grey-800 text-lavender-blush-100;
  }

  :global(a) {
    @apply text-pearl-aqua-300 underline underline-offset-2 hover:underline-offset-4;
    @apply transition-all duration-300 ease-in-out;
    @apply hover:text-pearl-aqua-100;
  }

  :global(a:visited) {
    @apply text-magenta-bloom-300;
    @apply hover:text-magenta-bloom-100;
  }
</style>
