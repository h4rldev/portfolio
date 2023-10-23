use pages::{index::Index, not_found::NotFound};
use std::fmt;
use yew::prelude::*;
use yew::Renderer;
use yew_router::prelude::*;
mod pages;

#[derive(Routable, PartialEq, Eq, Clone)]
pub enum Route {
    #[at("/")]
    Index,
    #[not_found]
    #[at("/404")]
    NotFound,
}

impl fmt::Display for Route {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        match self {
            Route::Index => write!(f, "Home"),
            Route::NotFound => write!(f, "404"),
        }
    }
}

fn switch(routes: Route) -> Html {
    match routes {
        Route::Index => html! { <Index /> },
        _ => html! { <NotFound /> },
    }
}

#[derive(Properties, Clone, PartialEq, Eq)]
pub struct GoToProps {
    #[prop_or(Route::Index.to_string())]
    pub route: String,
    #[prop_or(String::from(""))]
    pub route_nickname: String,
    #[prop_or(String::from("hover:text-puccin-teal cursor-pointer font-mono"))]
    pub class: String,
    #[prop_or((String::from(""), String::from("")))]
    pub message: (String, String),
}

#[function_component(GoTo)]
fn goto(props: &GoToProps) -> Html {
    let message: (String, String) = props.message.clone();
    let navigator = use_navigator().unwrap();
    let route = match props.route.as_str() {
        "Index" | "Home" => Route::Index,
        _ => Route::NotFound,
    };
    let onclick = Callback::from(move |_| {
        navigator.push(&route);
    });
    if props.route_nickname.is_empty() {
        html! {
            <>
                { message.0 }
                <a target="_self" {onclick} class={&props.class}>{ &props.route }</a>
                { message.1 }
            </>
        }
    } else {
        html! {
            <>
                { message.0 }
                <a target="_self" {onclick} class={&props.class}>{ &props.route_nickname }</a>
                { message.1 }
            </>
        }
    }
}

#[function_component(App)]
fn app() -> Html {
    html! {
        <html class="relative min-h-screen text-puccin-text text-lg overflow-hidden">
        <div class="absolute inset-0 bg-evening bg-cover bg-center blur-lg scale-110 overflow-hidden"></div>
            <BrowserRouter>
                <Switch<Route> render={switch} />
            </BrowserRouter>
        </html>
    }
}

fn main() {
    Renderer::<App>::new().render();
}
