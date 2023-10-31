use crate::utils::{Age, Button};
use yew::prelude::*;

#[function_component(Title)]
pub fn title() -> Html {
    html! {
        <>
            <title> { "h4rl" } </title>
            <p class="text-2xl/loose"> { "Hey, I'm " } <span class="text-puccin-teal"> { "Oscar Sjödin Jansson" } </span> </p>
            <p class="text-sm"> { "Also known as " } <span class="text-puccin-teal"> { "h4rl" } </span> { " or " } <span class="text-puccin-teal"> { "h4rl3h"} </span> { " on the interwebs." } </p>
            <p class="text-sm mb-7"> { "Currently " } <Age/> { " years old" } </p>
        </>

    }
}

#[function_component(Socials)]
pub fn socials() -> Html {
    html! {
        <>
            <h1 class="text-center mb-7"> { "Socials" } </h1>
            <div class="flex flex-wrap justify-center gap-5">
                // github
                <Button src="github.svg" alt="github logo" text="@h4rldev" href="github"/>
                // twitter
                <Button src="x.svg" alt="x logo" text="@h4rl3h" href="x"/>
                // discord
                <Button src="discord.svg" alt="discord logo" text="@h4rl" href="discord" />
                // linkedin
                <Button src="linkedin.png" alt="linkedin logo" text="Oscar Sjödin Jansson" href="linkedin" />
                // codeberg
                <Button src="codeberg.svg" alt="codeberg logo" text="@h4rl" href="codeberg" />
            </div>
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
            <Socials />
        </>
    }
}

#[function_component(Index)]
pub fn main() -> Html {
    html! {
        <div class="relative flex items-center justify-center h-screen">
            <div class="base">
                <Title />
                <Description />
            </div>
        </div>
    }
}
