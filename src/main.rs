use pages::{about::About, blog::Blog, index::Index, not_found::NotFound};
use yew::prelude::*;
use yew::Renderer;
use yew_router::prelude::*;

mod pages;

#[derive(Routable, PartialEq, Eq, Clone)]
pub enum RootRoute {
    #[at("/")]
    Index,
    #[at("/:s")]
    Route,
}

#[derive(Routable, PartialEq, Eq, Clone)]
pub enum Route {
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
        Route::About => html! { <About />  },
        Route::NotFound => html! { <NotFound /> },
        Route::Blog => html! { <Blog /> },
    }
}

fn root_route(routes: RootRoute) -> Html {
    match routes {
        RootRoute::Index => html! {
            <Index />
        },
        RootRoute::Route => html! {
            <BrowserRouter>
                <Switch<Route> render={switch} />
            </BrowserRouter>
        },
    }
}

#[function_component(GoBack)]
fn goback() -> Html {
    let navigator = use_navigator().unwrap();
    let back = Callback::from(move |_| navigator.back());
    html! {
        <a href="" target="_self" onclick={back} class="hover:text-teal-200">{ "Go back?" }</a>
    }
}

#[function_component(App)]
fn app() -> Html {
    html! {
        <BrowserRouter>
            <Switch<RootRoute> render={root_route} />
        </BrowserRouter>
    }
}

fn main() {
    Renderer::<App>::new().render();
}
