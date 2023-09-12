use crate::Route;
use yew::prelude::*;
use yew_router::prelude::*;

#[function_component(Title)]
pub fn title() -> Html {
    html! {
        <h1>{ "H4rl's Site" }</h1>
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
            <p> { "Navigate to:" }
            <a onclick={click_listener(navigator.clone(), "about")}>{ "About" }</a>
            <a onclick={click_listener(navigator.clone(), "blog")}>{ "Blog" }</a>
            <a onclick={click_listener(navigator.clone(), "404")}>{ "404" }</a>
            </p>
        </>
    }
}
