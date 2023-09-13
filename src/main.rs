use pages::{about::About, blog::Blog, index::Index, not_found::NotFound};
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
    #[prop_or(Route::Index)]
    pub route: Route,
    #[prop_or(("Go to".to_string(), "?".to_string()))]
    pub message: (String, String),
}

#[function_component(GoTo)]
fn goto(props: &GoToProps) -> Html {
    let route: Route = props.route.clone();
    let message: (String, String) = props.message.clone();
    let navigator = use_navigator().unwrap();
    let push_route = route.clone();
    let onclick = Callback::from(move |_| {
        navigator.push(&push_route);
    });
    match route {
        Route::About => {
            html! {
            <p>{ message.0.as_str() }
                <a href="" target="_self" {onclick} class="hover:text-teal-200">{ "Go to About?" }</a>
                { message.1.as_str() }
            </p>
            }
        }
        Route::Blog => {
            html! {
                <p>{ message.0.as_str() }
                    <a href="" target="_self" {onclick} class="hover:text-teal-200">{ "Blog?" }</a>
                    { message.1.as_str() }
                </p>
            }
        }
        Route::Index => {
            html! {
                <p>{ message.0.as_str() }
                    <a href="" target="_self" {onclick} class="hover:text-teal-200">{ "Home" }</a>
                    { message.1.as_str() }
                </p>
            }
        }
        _ => {
            html! {
                <p>{ "Go to " }
                    <a href="" target="_self" {onclick} class="hover:text-teal-200">{ "???" }</a>
                </p>
            }
        }
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
