<script lang="ts">
  let { direction = "none", children } = $props();

  // Reactive class based on direction
  $effect(() => {
    // Add any side effects here if needed
  });
</script>

<div
  class="slide-wrapper"
  class:slide-left={direction === 'left'}
  class:slide-right={direction === 'right'}
  class:slide-up={direction === 'up'}
  class:slide-down={direction === 'down'}
>
  {@render children?.()}
</div>

<style>
  .slide-wrapper {
    transition: transform 0.4s cubic-bezier(0.4, 0, 0.2, 1);
    will-change: transform;
    min-height: 100vh;
    min-width: 100vw;
    max-width: 100vw;
  }

  .slide-left {
    transform: translateX(-40vw);
    overflow: hidden !important;
  }

  .slide-right {
    transform: translateX(40vw);
    overflow: hidden !important;
  }

  .slide-up {
    transform: translateY(-50vh);
    overflow: hidden !important;
  }

  .slide-down {
    transform: translateY(50vh);
    overflow: hidden !important;
  }
</style>
