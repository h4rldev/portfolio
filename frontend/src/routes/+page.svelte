<script>
	import Nav from '$components/Nav.svelte';
	import Glass from '$components/Glass.svelte';
</script>

<svelte:head>
	<title>Hello</title>
</svelte:head>

<header>
	<Nav />
</header>
<main>
	<Glass>
		{#snippet content()}
			<h1>Hi</h1>
		{/snippet}
	</Glass>
</main>
<footer></footer>

<style></style>
