use pages::{about::About, blog::Blog, index::Index, not_found::NotFound};
use std::fmt;
use yew::prelude::*;
use yew::Renderer;
use yew_router::prelude::*;

mod pages;

#[derive(Routable, PartialEq, Eq, Clone)]
pub enum Route {
    #[at("/")]
    Index,
    #[at("/about")]
    About,
    #[at("/blog")]
    Blog,
    #[not_found]
    #[at("/404")]
    NotFound,
}

impl fmt::Display for Route {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        match self {
            Route::Index => write!(f, "Home"),
            Route::About => write!(f, "About"),
            Route::Blog => write!(f, "Blog"),
            Route::NotFound => write!(f, "404"),
        }
    }
}

fn switch(routes: Route) -> Html {
    match routes {
        Route::Index => html! { <Index /> },
        Route::About => html! { <About />  },
        Route::NotFound => html! { <NotFound /> },
        Route::Blog => html! { <Blog /> },
    }
}

#[derive(Properties, Clone, PartialEq, Eq)]
pub struct GoToProps {
    #[prop_or(Route::Index.to_string())]
    pub route: String,
    #[prop_or(("Go to ".to_string(), "?".to_string()))]
    pub message: (String, String),
}

#[function_component(GoTo)]
fn goto(props: &GoToProps) -> Html {
    let message: (String, String) = props.message.clone();
    let navigator = use_navigator().unwrap();
    let route = match props.route.as_str() {
        "Index" | "Home" => Route::Index,
        "About" => Route::About,
        "Blog" => Route::Blog,
        _ => Route::NotFound,
    };
    let onclick = Callback::from(move |_| {
        navigator.push(&route);
    });
    html! {
        <>
            { message.0.as_str() }
            <a href="" target="_self" {onclick} class="hover:text-teal-200">{ &props.route.as_str() }</a>
            { message.1.as_str()}
        </>
    }
}

#[function_component(App)]
fn app() -> Html {
    html! {
        <BrowserRouter>
            <Switch<Route> render={switch} />
        </BrowserRouter>
    }
}

fn main() {
    Renderer::<App>::new().render();
}
