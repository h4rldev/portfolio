<script>
	import Nav from '$components/Nav.svelte';
	import Footer from '$components/Footer.svelte';
</script>

<svelte:head>
	<title>Hello</title>
</svelte:head>

<header>
	<Nav />
</header>
<main></main>
<footer>
	<Footer />
</footer>

<style>
	header {
		@apply mb-12 mt-8;
	}

	main {
		@apply mb-0 mt-4 flex flex-row justify-center;
	}

	footer {
		@apply flex flex-row justify-center;
	}
</style>
