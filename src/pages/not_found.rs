use crate::GoTo;
use yew::prelude::*;

#[function_component(NotFound)]
pub fn main() -> Html {
    html! {
        <>
            <div class="relative h-screen flex">
                <div class="m-auto text-center">
                    <img class="object-contain h-[325px] w-[375px] items-center" src="https://http.cat/404"/>
                    <GoTo route="Index" route_nickname="Return to Home?" message={("".to_string(), "".to_string())} />
                </div>
            </div>
        </>
    }
}
