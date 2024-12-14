<script>
</script>

<nav>
	<ul>
		<li><div>h4rl</div></li>
		<li>
			<a href="/">home</a>
		</li>
		<li>
			<a href="/posts">posts</a>
		</li>
		<li>
			<a href="/portfolio">portfolio</a>
		</li>
	</ul>
</nav>

<style>
	nav {
		@apply flex flex-row justify-center;
	}

	li:nth-child(1) {
		@apply mx-6;
	}

	a {
		@apply h-[24px];
	}

	ul {
		@apply font-nova;
		@apply inline-flex w-[80%] min-w-[360px] flex-row gap-3 rounded-xl bg-white bg-opacity-10 px-4 py-2 outline outline-2 outline-gray-500 backdrop-blur-sm;
	}
</style>
