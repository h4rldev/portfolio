use utils::router::{switch, Route};
use yew::prelude::*;
use yew::Renderer;
use yew_router::prelude::*;
mod pages;
mod utils;

#[function_component(App)]
fn app() -> Html {
    html! {
        <main class="main">
            <section class="relative">
                <section class="bg"></section>
                <section class="bg-blur"></section>
                <section class="relative">
                    <BrowserRouter>
                        <Switch<Route> render={switch} />
                    </BrowserRouter>
                </section>
            </section>
        </main>
    }
}

fn main() {
    Renderer::<App>::new().render();
}
