<script>
	import DarkMode from '$components/DarkMode.svelte';
</script>

<div>
	<nav>
		<ul>
			<li class="togglable">
				<a href="/">home</a>
			</li>
			<li class="togglable">
				<a href="/posts">posts</a>
			</li>
			<li class="togglable">
				<DarkMode />
			</li>
		</ul>
	</nav>
</div>

<style>
</style>
