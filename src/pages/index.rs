use crate::Route;
use yew::prelude::*;
use yew_router::prelude::*;

#[function_component(Title)]
pub fn title() -> Html {
    html! {
        <h1 class="font-medium text-xl subpixel-antialiased">{ "H4rl's Site" }</h1>
    }
}

fn click_listener(nav: Navigator, name: &str) -> Callback<MouseEvent> {
    match name {
        "about" => Callback::from(move |_| {
            nav.replace(&Route::About);
        }),

        "blog" => Callback::from(move |_| {
            nav.replace(&Route::Blog);
        }),

        _ => Callback::from(move |_| {
            nav.replace(&Route::NotFound);
        }),
    }
}

#[function_component(Index)]
pub fn main() -> Html {
    let navigator = use_navigator().unwrap();

    html! {
        <>
            <Title />
            <a href="" target="_self" onclick={click_listener(navigator.clone(), "about")} class="hover:bg-blue">{ "About" }</a> <br />
            <a href="" target="_self" onclick={click_listener(navigator.clone(), "blog")} class="hover:bg-blue">{ "Blog" }</a> <br />
            <a href="" target="_self" onclick={click_listener(navigator.clone(), "404")} class="hover:bg-blue">{ "404" }</a>
        </>
    }
}
