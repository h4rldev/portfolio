<Glass>
	<section class="intro">
		<div class="text-holder">
			<div>
				<div class="specialize">
					<p>{m.specialize()} {m.environments()}, {m.ilikeusing()}</p>
					<p>C, Rust, Bash, Javascript, TypeScript, ... {m.andmore()}</p>
				</div>
				<div class="frameworks">
					<p>{m.ilikeframeworks()}:</p>
					<p>{m.frameworks()}</p>
				</div>
				<p>{m.interests()}</p>
			</div>
		</div>
		<div class="lastfm-container">
			<p>{m.lastfm()}</p>
			<LastFM />
		</div>
	</section>
	<section class="socials">
		<h1>{m.socials()}</h1>
		<ul class="socials-list">
			<li>
				<a href="https://github.com/h4rldev" target="_blank">
					<Icon icon="simple-icons:github" class="inline-block h-[2rem] w-[2rem]" />
				</a>
			</li>
			<li>
				<a href="https://bsky.app/profile/h4rl.dev" target="_blank">
					<Icon icon="simple-icons:bluesky" class="inline-block h-[2rem] w-[2rem]" />
				</a>
			</li>
			<li>
				<a href="https://www.last.fm/user/h4rl3h" target="_blank">
					<Icon icon="simple-icons:lastdotfm" class="inline-block h-[2rem] w-[2rem]" />
				</a>
			</li>
			<li>
				<a href="https://discord.com/users/275689969601871882" target="_blank">
					<Icon icon="simple-icons:discord" class="inline-block h-[2rem] w-[2rem]" />
				</a>
			</li>
		</ul>
		{#if isEmailOpen}
			<div class="email-container">
				<a href="mailto:contact@h4rl.dev" target="_blank">contact@h4rl.dev</a>
			</div>
		{:else}
			<button class="fake-link" onclick={() => (isEmailOpen = !isEmailOpen)}>
				{m.email()}
			</button>
		{/if}
	</section>
	<section class="friends-communities-and-lastfm">
		<div class="friends-communities">
			<div>
				<ExpandableList list_items={frens}>
					{#snippet button_text()}
						{m.friends()}
					{/snippet}
					{#snippet button_icon_open()}
						<Icon icon="iwwa:arrow-up" class="inline-block h-[1rem] w-[1rem]" />
					{/snippet}
					{#snippet button_icon_close()}
						<Icon icon="iwwa:arrow-down" class="inline-block h-[100%] w-[100%]" />
					{/snippet}
				</ExpandableList>
			</div>
			<div>
				<ExpandableList list_items={communities}>
					{#snippet button_text()}
						{m.communities()}
					{/snippet}
					{#snippet button_icon_open()}
						<Icon icon="iwwa:arrow-up" class="inline-block h-[1rem] w-[1rem]" />
					{/snippet}
					{#snippet button_icon_close()}
						<Icon icon="iwwa:arrow-down" class="inline-block h-[100%] w-[100%]" />
					{/snippet}
				</ExpandableList>
			</div>
		</div>
		<div class="my-banner">
			<p>My 88x31</p>
			<img src="/88x31/me.png" class="eight-eight-ecks-thirty-one" alt="me" />
			<p>Feel free to copy it if you want.</p>
		</div>
	</section>
	<section></section>
</Glass>
