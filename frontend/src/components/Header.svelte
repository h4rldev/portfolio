<script lang="ts">
  import { browser } from "$app/environment";
  import { page } from "$app/stores";
</script>

<div class="name-container flex flex-row justify-center py-10 items-center gap-3">
  <img src="/imissyou.jpg" alt="I miss you kitty :C" class="kitty-img" />
  <div>
    <h1>
      <span class="rainbow">h4rl</span>.<span class="text-pearl-aqua-300 dev">dev</span>
    </h1>
    <p class="text-shadow-grey-300">(he/they)</p>
  </div>
</div>

<nav>
  <ul>
    <li aria-current={$page.url.pathname === "/" ? "page" : undefined}>
      <a href="/">
        <span>Home</span>
        <div>/</div>
      </a>
    </li>

    <li aria-current={$page.url.pathname === "/blog/" ? "page" : undefined}>
      <a href="/blog">
        <span>Blog</span>
        <div>/blog</div>
      </a>
    </li>

    <li aria-current={$page.url.pathname === "/projects/" ? "page" : undefined}>
      <a href="/projects">
        <span>Projects</span>
        <div>/projects</div>
      </a>
    </li>

    <li aria-current={$page.url.pathname === "/contact/" ? "page" : undefined}>
      <a href="/contact">
        <span>Contact</span>
        <div>/contact</div>
      </a>
    </li>
  </ul>
</nav>

<style>
  @reference 'appcss';

  .kitty-img {
    @apply w-25 h-auto border-pearl-aqua-300 border-2 border-dotted p-1 rounded-full;
  }

  .dev {
    text-shadow: 0 0 10px rgba(255, 255, 255, 0.2), 0 0 20px rgba(255, 255, 255, 0.2);
  }

  .rainbow {
	  --angle: 0deg;
	  background: conic-gradient(from var(--angle), red, yellow, lime, aqua, blue, magenta, red);
	  animation: 5s rotate linear infinite;
    text-shadow:
    0 0 5px rgba(255, 255, 255, 0.2),
    0 0 10px rgba(255, 255, 255, 0.2),
    0 0 15px rgba(255, 255, 255, 0.2),
    0 0 20px rgba(255, 255, 255, 0.2);
    @apply pt-8 text-transparent bg-clip-text;
  }

  @keyframes rotate {
	  to {
		  --angle: 360deg;
	  }
  }

  @property --angle {
    syntax: '<angle>';
    initial-value: 0deg;
    inherits: false;
  }

  li[aria-current='page']:not(:first-child)::after {
    content: "";
    @apply absolute block w-[calc(100%-14px)] h-full bg-pearl-aqua-300 top-2 left-3.5 rounded-md bg-transparent border-pearl-aqua-300 border-b-2 -z-1;
  }

  li[aria-current='page']:first-child::after {
    content: "";
    @apply absolute block w-full h-full bg-transparent top-2 rounded-md border-pearl-aqua-300 border-b-2 -z-1;
  }

  li[aria-current='page']:first-child a::after {
    content: "";
    @apply absolute block w-[0px] h-[0px] top-[110%] left-[45%];

    border-left: 5px solid transparent;
    border-right: 5px solid transparent;
    border-bottom: 5px solid var(--color-pearl-aqua-300);
  }

  li[aria-current='page']:not(:first-child) a::after {
    content: "";
    @apply absolute block w-[0px] h-[0px] top-[110%] left-[50%];

    border-left: 5px solid transparent;
    border-right: 5px solid transparent;
    border-bottom: 5px solid var(--color-pearl-aqua-300);
  }

  h1 {
    @apply text-4xl font-bold text-center inline;
  }

  nav {
    @apply flex flex-row justify-between w-full justify-center;
  }

  ul {
    @apply flex flex-row gap-4 text-lg flex-wrap justify-center;
  }

  li {
    @apply flex flex-row items-center relative z-1;
  }

  a {
    @apply decoration-transparent;
  }

  a span {
    @apply decoration-pearl-aqua-300 underline;
    @apply transition-all duration-300 ease-in-out;
  }

  a:hover span {
    @apply decoration-pearl-aqua-100;
  }

  a:visited span {
    @apply decoration-magenta-bloom-300 underline;
  }

  a:hover:visited span {
    @apply decoration-magenta-bloom-100;
  }

  ul li:not(:first-child)::before {
    content: "";
    @apply block w-[2px] h-[1em] bg-reddish-brown-200 mr-3;
  }

  nav div {
    @apply no-underline inline-block text-shadow-grey-500 bg-shadow-grey-dark;
    @apply px-2;
  }

  @media (orientation: portrait) {
    ul {
      @apply gap-2;
    }

    nav div {
      @apply hidden;
    }

    li[aria-current='page']::after {
      @apply border-none;
    }

    li[aria-current='page']:first-child a::after {
      border-left: 0px;
      border-right: 0px;
      border-bottom: 0px;
    }

    li[aria-current='page']:not(:first-child) a::after {
      border-left: 0px;
      border-right: 0px;
      border-bottom: 0px;
    }

    ul li:last-child::before {
      @apply hidden;
    }
  }

  @media (min-width: 768px) {
    ul li:last-child::before {
      content: "";
      @apply block w-[2px] h-[1em] bg-reddish-brown-200 mr-3;
    }
  }
</style>
