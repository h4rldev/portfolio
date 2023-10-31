use utils::{switch, Route};
use yew::prelude::*;
use yew::Renderer;
use yew_router::prelude::*;
mod pages;
mod utils;

#[function_component(App)]
fn app() -> Html {
    html! {
        <html class="main">
            <div class="relative">
                <div class="bg"></div>
                <div class="bg-blur"></div>
                <div class="relative">
                    <BrowserRouter>
                        <Switch<Route> render={switch} />
                    </BrowserRouter>
                </div>
            </div>
        </html>
    }
}

fn main() {
    Renderer::<App>::new().render();
}
