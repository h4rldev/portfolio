<script lang="ts">
  import { SvelteDate } from "svelte/reactivity";
  import Heading from "$components/Heading.svelte";

  const birthDate = new Date("2005-09-02");
  const now = new SvelteDate();
  $effect(() => {
    const interval = setInterval(() => {
      now.setTime(Date.now());
    }, 1);
    return () => clearInterval(interval);
  });

  const age = $derived(
    ((now.getTime() - birthDate.getTime()) / 31556926000).toFixed(8),
  );
</script>

<section>
  <Heading type="h2">Welcome!</Heading>
  <p>Hiii, I'm h4rl, a {age} year old currently self-studying Full-Stack development.</p>
  <br />
  <p>I love programming silly projects, playing games (currently loving playing with friends through <a href="https://archipelago.gg" target="_blank">Archipelago</a>), reading manga, listening to music, watching anime and studying niche projects on GitHub!</p>
  <br />
  <p>I've been scripting since 2018 and been programming since 2022, having experimented with WebDev for longer than that.</p>
  <br />
  <p>This website serves as a small portfolio and also a blog where I share my thoughts and projects, so grab a drink and enjoy the read (if you can).</p>
</section>
<section class="c8831">
  <ul>
    <li>
      <img src="/88x31/built-with-nix.gif" alt="Built with Nix" />
    </li>
    <li>
      <img src="/88x31/made-w-nvim.png" alt="Made with Neovim" />
    </li>
    <li>
      <img src="/88x31/svelte.png" alt="Svelte" />
    </li>
    <li>
      <img src="/88x31/cookiefree.gif" alt="This site is 100% cookie free!" />
    </li>
    <li>
      <img src="/88x31/queercoded.png" alt="You're telling me a queer coded this" />
    </li>
    <li>
      <img src="/88x31/pan.png" alt="Pansexual Pride Flag" />
    </li>
    <li>
      <img src="/88x31/trans-rights-now.png" alt="Trans rights now!" />
    </li>
    <li>
      <img src="/88x31/pride-flag.gif" alt="Pride for everyone" />
    </li>
    <li>
      <a href="https://eightyeightthirty.one" target="_blank">
        <img src="/88x31/eightyeightthirtyone.png" alt="eighty eight thirty one" />
      </a>
    </li>
  </ul>
</section>
<section class="mt-6">
  <img src="/me.jpeg" alt="Me" class="me-img" />
</section>

<style>
  @reference 'appcss';

  .me-img {
    @apply w-120 h-auto;
  }

  .c8831 {
    @apply mt-6;
  }

  section {
    @apply max-w-[800px];
    @apply mx-0;
    @apply px-0;
  }

  ul {
    @apply flex flex-row gap-1 flex-wrap justify-center;
  }

  ul li img {
    @apply w-[88px] h-[31px];
    image-rendering: pixelated;
  }

  @media (orientation: portrait) {
    section, .me-img {
      @apply max-w-[80vw];
    }
  }
</style>
