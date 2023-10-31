use crate::pages::{index::Index, not_found::NotFound};
use chrono::{DateTime, Utc};
use gloo_timers::callback::Interval;
use std::fmt;
use web_sys::window;
use yew::prelude::*;
use yew_router::prelude::*;

#[derive(Routable, PartialEq, Eq, Clone)]
pub enum Route {
    #[at("/")]
    Index,
    #[at("/linkedin")]
    Linkedin,
    #[at("/github")]
    Github,
    #[at("/discord")]
    Discord,
    #[at("/x")]
    X,
    #[at("/rickroll")]
    RickRoll,
    #[at("/codeberg")]
    Codeberg,
    #[not_found]
    #[at("/404")]
    NotFound,
}

impl fmt::Display for Route {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        match self {
            Route::Index => write!(f, "/"),
            Route::NotFound => write!(f, "404"),
            Route::Linkedin => write!(f, "/linkedin"),
            Route::Github => write!(f, "/github"),
            Route::Discord => write!(f, "/discord"),
            Route::RickRoll => write!(f, "/rickroll"),
            Route::Codeberg => write!(f, "/codeberg"),
            Route::X => write!(f, "/x"),
        }
    }
}

pub fn switch(routes: Route) -> Html {
    match routes {
        Route::Index => html! { <Index /> },
        Route::Discord
        | Route::Github
        | Route::Linkedin
        | Route::RickRoll
        | Route::X
        | Route::Codeberg => {
            html! { <Redirect route={routes.to_string()} /> }
        }
        _ => html! { <NotFound /> },
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
    let navigator = use_navigator().expect("Navigator not found");
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

    let onclick =
        Callback::from(move |_| navigator.push(&Route::recognize(&button_props.href).unwrap()));

    html! {
        <button
            class={classes!("buttonwithicon", {button_props.extra_class})}
            onmouseover={on_mouse_over}
            onmouseout={on_mouse_out}
            onclick={onclick}
        >
            <img
                class={classes!(if *hover { "invert" } else { "" })}
                src={button_props.src}
                alt={button_props.alt}
            />
            { button_props.text }
        </button>
    }
}

#[derive(Properties, Clone, PartialEq, Eq)]
pub struct RedirectProps {
    pub route: String,
}

#[function_component(Redirect)]
pub fn redirect(props: &RedirectProps) -> Html {
    let urls: [&str; 7] = [
        "https://www.linkedin.com/in/oscar-sj%C3%B6din-jansson-528894295",
        "https://github.com/h4rldev",
        "https://discord.com/users/275689969601871882",
        "https://twitter.com/h4rl3h",
        "https://www.youtube.com/watch?v=dQw4w9WgXcQ",
        "https://codeberg.org/h4rl",
        "https://h4rl.is-a.dev/404",
    ];
    let properties = props.clone();
    let url = match properties.route.as_str() {
        "/linkedin" => urls[0],
        "/github" => urls[1],
        "/discord" => urls[2],
        "/x" => urls[3],
        "/rickroll" => urls[4],
        "/codeberg" => urls[5],
        _ => urls[6],
    };
    let window = window().expect("no global `window` exists");
    let location = window.location();
    let _ = location.replace(url);
    html! {
        <div class="relative flex h-screen overflow-hidden">
            <div class="font-mono m-auto bg-puccin-base p-16 rounded-3xl overflow-hidden">
                <h1>{ "Redirecting to " } <span class="link hover:text-puccin-teal">{url}</span> </h1>
            </div>
        </div>
    }
}
