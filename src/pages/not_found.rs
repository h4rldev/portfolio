use crate::Route;
use yew::prelude::*;
use yew_router::prelude::Link;

#[function_component(NotFound)]
pub fn main() -> Html {
    html! {
        <>
            <title> { "Not found" } </title>
            <div class="relative h-screen flex">
                <div class="m-auto text-center">
                    <img class="object-contain h-[325px] w-[375px] items-center" src="https://http.cat/404"/>
                    <Link<Route> to={Route::Index}><button class="button"> { "Go back" } </button></Link<Route>>
                </div>
            </div>
        </>
    }
}
