use crate::pages::{about::About, index::Index, not_found::NotFound, projects::Projects};
use gloo_timers::callback::Timeout;
use std::fmt;
use web_sys::window;
use yew::prelude::*;
use yew_router::prelude::*;

#[derive(Routable, PartialEq, Eq, Clone)]
pub enum Route {
    // Pages
    #[at("/")]
    Index,
    #[at("/about")]
    About,
    #[at("/projects")]
    Projects,
    #[not_found]
    #[at("/404")]
    NotFound,

    // Redirects
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
}

impl fmt::Display for Route {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        match self {
            // Pages
            Route::Index => write!(f, "/"),
            Route::About => write!(f, "/about"),
            Route::Projects => write!(f, "/projects"),
            Route::NotFound => write!(f, "404"),

            // Redirects
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
    match &routes {
        Route::Index => html! { <Index /> },
        Route::About => html! { <About /> },
        Route::Projects => html! { <Projects /> },
        Route::Discord
        | Route::Github
        | Route::Linkedin
        | Route::RickRoll
        | Route::Codeberg
        | Route::X => html! { <Redirect route={routes.to_string()} /> },
        _ => html! { <NotFound /> },
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
    use_effect(move || {
        let timeout = Timeout::new(500, move || {
            let _ = location.replace(url);
        });

        timeout.forget();

        || {}
    });

    html! {
        <div class="relative flex h-screen overflow-hidden">
            <div class="font-mono m-auto bg-puccin-base p-16 rounded-3xl overflow-hidden">
                <h1>{ "Redirecting to " } <span class="link hover:text-puccin-teal">{url}</span> </h1>
            </div>
        </div>
    }
}
