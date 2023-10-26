//use crate::Meta;
use chrono::{DateTime, Utc};
use gloo_timers;
use gloo_timers::callback::Interval;
use wasm_bindgen::JsCast;
use web_sys::window;
use web_sys::HtmlElement;
use yew::functional::*;
use yew::prelude::*;

#[function_component(Index)]
pub fn main() -> Html {
    html! {
        <div class="relative flex h-screen overflow-hidden">
            <div class="font-mono m-auto bg-puccin-base p-16 rounded-3xl overflow-hidden">
                <Title />
                <Description />
            </div>
        </div>
    }
}

#[function_component(Age)]
pub fn age() -> Html {
    let age = use_state(calculate_age);

    let age_for_effect = age.clone();
    use_effect(move || {
        let age = age.clone();
        let interval = Interval::new(0, move || {
            age.set(calculate_age());
        });

        interval.forget();

        || {}
    });

    let age_for_render = age_for_effect;
    html! {
        <span class="text-puccin-teal"> { format!("{:.15}", *age_for_render) } </span>
    }
}

fn calculate_age() -> f64 {
    let birthday = DateTime::parse_from_rfc2822("Fri, 2 Sep 2005 00:00:00 +0100").unwrap();
    let now = Utc::now();
    let age_seconds = now.timestamp() - birthday.timestamp();
    age_seconds as f64 / 60.0 / 60.0 / 24.0 / 365.0
}

#[function_component(Socials)]
pub fn socials() -> Html {
    html! {
        <>
            <h1 class="text-center mb-7"> { "Socials" } </h1>
            <div class="flex justify-center">
                // github
                <Button src="github.svg" alt="github logo" text="@h4rldev" href="https://github.com/h4rldev" extra_class="mr-10"/>
                // twitter
                <Button src="x.svg" alt="x logo" text="@h4rl3h" href="https://twitter.com/h4rl3h" extra_class="mr-10"/>
                // discord
                <Button src="discord.svg" alt="discord logo" text="@h4rl" href="https://discord.com/users/275689969601871882" extra_class="mr-10" />

                <Button src="linkedin.png" alt="linkedin logo" text="Oscar Sjödin Jansson" href="https://www.linkedin.com/in/oscar-sj%C3%B6din-jansson-528894295/"/>
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

#[derive(Properties, Clone, PartialEq, Eq)]
pub struct ButtonProps {
    #[prop_or_default]
    pub src: String,
    #[prop_or("".to_string())]
    pub alt: String,
    #[prop_or_default]
    pub text: String,
    #[prop_or("".to_string())]
    pub href: String,
    #[prop_or("".to_string())]
    pub extra_class: String,
}

#[function_component(Button)]
pub fn button(props: &ButtonProps) -> Html {
    let button_props = props.clone();
    let hover = use_state(|| false);

    let on_mouse_over = {
        let hover = hover.clone();
        Callback::from(move |_| hover.set(true))
    };

    let on_mouse_out = {
        let hover = hover.clone();
        Callback::from(move |_| hover.set(false))
    };

    let onclick = Callback::from(move |_| {
        let window = window().expect("no global `window` exists");
        let document = window.document().expect("should have a document on window");
        let body = document.body().expect("document should have a body");

        let anchor = document.create_element("a").unwrap();
        anchor.set_attribute("href", &button_props.href).unwrap();
        anchor.set_attribute("target", "_blank").unwrap();

        body.append_child(&anchor).unwrap();

        // Click the anchor element to open the new tab
        let html_element = JsCast::dyn_into::<HtmlElement>(anchor).unwrap();
        html_element.click();
    });

    html! {
        <button
            class={classes!("button", {button_props.extra_class})}
            onmouseover={on_mouse_over}
            onmouseout={on_mouse_out}
            onclick={onclick}
        >
            <img
                class={classes!("h-6", "w-6", "mr-2", if *hover { "invert" } else { "" })}
                src={button_props.src}
                alt={button_props.alt}

            />

            { button_props.text }
        </button>
    }
}

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
