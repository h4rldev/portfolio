use stylist::yew::use_style;
use yew::prelude::*;
use yew::Renderer;
use yew_router::prelude::*;
use yew_router::switch::SwitchProps;

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
        Route::About => html! { <p>{ "About" }</p> },
        Route::NotFound => html! { <p>{ "Not Found" }</p> },
        Route::Blog => html! { <p>{ "Blog" }</p> },
    }
}

fn root_route(routes: RootRoute) -> Html {
    match routes {
        RootRoute::Index => html! { <p class="text-4xl">{ "H4rl" }</p> },
        RootRoute::Route => html! {
            <main>
                    <Switch<Route> render={switch} />
            </main>
        },
    }
}

#[function_component(App)]
fn app() -> Html {
    html! {
        <BrowserRouter>
            <main>
                <Switch<RootRoute> render={root_route} />
            </main>
        </BrowserRouter>
    }
}

fn main() {
    Renderer::<App>::new().render();
}
