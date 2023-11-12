use crate::utils::{
    components::{Age, Button},
    router::Route,
};
use yew::prelude::*;
use yew_router::prelude::*;

#[function_component(Title)]
pub fn title() -> Html {
    html! {
        <>
            <title> { "h4rl" } </title>
            <p class="text-2xl/loose"> { "Hey, I'm " } <span class="text-puccin-teal"> { "Oscar Sjödin Jansson" } </span> </p>
            <p class="text-sm"> { "Also known as " } <span class="text-puccin-teal"> { "h4rl" } </span> { " or " } <span class="text-puccin-teal"> { "h4rl3h"} </span> { " on the interwebs." } </p>
            <p class="text-sm"> { "Currently " } <Age/> { " years old" } </p>
        </>
    }
}

#[function_component(Socials)]
pub fn socials() -> Html {
    html! {
        <>
            <h1 class="text-center"> { "Socials" } </h1>
            <section class="flex flex-wrap justify-center gap-5 relative">
                // github
                <Button icon_class="i-[simple-icons--github]" alt="github logo" text="@h4rldev" href="github"/>
                // twitter
                <Button icon_class="i-[simple-icons--twitter]" alt="x logo" text="@h4rl3h" href="x"/>
                // discord
                <Button icon_class="i-[simple-icons--discord]" alt="discord logo" text="@h4rl" href="discord" />
                // linkedin
                <Button icon_class="i-[simple-icons--linkedin]" alt="linkedin logo" text="Oscar Sjödin Jansson" href="linkedin" />
                // codeberg
                <Button icon_class="i-[simple-icons--codeberg]" alt="codeberg logo" text="@h4rl" href="codeberg" />
            </section>
        </>
    }
}

#[function_component(Description)]
pub fn description() -> Html {
    html! {
        <>
            <p class="mb-7">
                { "I'm a self-taught " }
                <a class="rust" href="https://www.rust-lang.org/">
                    { "Rust" }
                </a>
                { ", " }
                <a class="python" href="https://www.python.org/">
                    { "Python" }
                </a>
                { " & " }
                <a class="bash" href="https://www.gnu.org/software/bash/">
                    { "Bash"}
                </a>
                { " programmer based in " }
                <span class="sweden">
                    { "Sweden" }
                </span>
                { "." }
            </p>
            <p> { "Aswell as an aspiring:" } </p>
            <ul class="inline-block list-square text-left ml-10 mb-7">
                <li> <p class="text-puccin-blue"> { "Computer Technician" } </p> </li>
                <li> <p class="text-puccin-blue"> { "Network Technician" } </p> </li>
                <li> <p class="text-puccin-blue"> { "Game Developer" } </p> </li>
                <li> <p class="text-puccin-blue"> { "System Administrator" } </p> </li>
            </ul>
            <p> { "I'm currently working on:" } </p>
            <ul class="inline-block list-square text-left ml-10 mb-7">
                <li> <a href="https://github.com/h4rldev/portfolio" class="project"> { "portfolio" } </a> </li>
                <li> <a href="https://github.com/h4rldev/discord-rpc-lastfm" class="project"> { "Discord RPC last.fm" } </a> </li>
                <li> <a href="https://github.com/h4rldev/windows-toolkit" class="project"> { "Windows Toolkit" } </a> </li>
                <li> <a href="https://github.com/h4rldev/check_elevation" class="project"> { "check_elevation" } </a> </li>
                <li> <a href="https://github.com/ani-rs/ani" class="project"> { "ani" } </a> </li>
            </ul>
        </>
    }
}

#[function_component(Footer)]
pub fn footer() -> Html {
    html! {
        <section class="footer">
            <Socials />
            <p>
                { "Made with " }
                <span class="text-puccin-red"> { "❤" } </span>
                { " by " }
                <span class="text-puccin-teal"> { "h4rl" } </span>
                { "." }
                <p>
                    { "Uses the " }
                    <a target="_blank" class="link text-puccin-green" href="https://github.com/h4rldev/portfolio/blob/main/LICENSE"> { "BSD 3-Clause License" } </a>
                    { "." }
                </p>
            </p>
        </section>
    }
}

#[derive(Properties, Clone, PartialEq)]
pub struct MaximizeProps {
    pub clicked: UseStateHandle<bool>,
}

#[function_component(Maximize)]
pub fn maximize(clicked: &MaximizeProps) -> Html {
    let onclick = {
        let clicked = clicked.clicked.clone();
        Callback::from(move |_| clicked.set(!*clicked))
    };
    html! {
        <button {onclick} aria-label="Minimize And Maximize" class="right-2 top-2 absolute">
            <svg class="text-puccin-green" height="20" width="20" xmlns="http://www.w3.org/2000/svg">
                <circle cx="10" cy="10" r="10" fill="currentColor" />
            </svg>
        </button>
    }
}

#[function_component(Navigation)]
pub fn navigation() -> Html {
    let hover = use_state(|| false);
    let onmouseover = {
        let hover = hover.clone();
        Callback::from(move |_| hover.set(true))
    };
    let onmouseout = {
        let hover = hover.clone();
        Callback::from(move |_| hover.set(false))
    };
    html! {
        <>
            <nav {onmouseover} {onmouseout} class={classes!( "navigation", if *hover { "move-down" } else { "move-up" })}>
                <ul class="nav-list">
                    <li> <Link<Route> to={Route::Index}> { "Home" } </Link<Route>> </li>
                    <li> <Link<Route> to={Route::Projects}> { "Projects" } </Link<Route>> </li>
                    <li> <Link<Route> to={Route::About}> { "About" } </Link<Route>> </li>
                </ul>
                <section class="nav-tab">
                    { "=" }
                </section>
            </nav>
        </>
    }
}

#[function_component(Index)]
pub fn main() -> Html {
    let clicked = use_state(|| false);
    let body_classes = classes!(if *clicked { "maximized" } else { "base" });
    html! {
        <main class="relative flex flex-col items-center justify-center h-screen">
            <Navigation/>
            <section class={body_classes}>
                <Maximize clicked={clicked.clone()} />
                <Title />
                <Description />
                <Footer />
            </section>
        </main>
    }
}
