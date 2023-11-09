use crate::Route;
use yew::prelude::*;
use yew_router::prelude::*;

#[function_component(NotFound)]
pub fn main() -> Html {
    let navigator = use_navigator().unwrap();
    let onclick = Callback::from(move |_| navigator.replace(&Route::Index));
    html! {
        <>
            <title> { "Not found" } </title>
            <main class="relative flex items-center justify-center h-screen flex-col">
                <img class="h-[325px] w-[375px] items-center" src="https://http.cat/404"/>
                <section class="not-found-button-container justify-center w-[375px]">
                    <button {onclick} class="button"> { "Go back" } </button>
                </section>
            </main>
        </>
    }
}
