use crate::GoBack;
use yew::prelude::*;
use yew_router::prelude::*;

#[function_component(Title)]
pub fn title() -> Html {
    html! {
        <h1>{ "404" }</h1>
    }
}

pub fn back_listener(nav: Navigator) -> Callback<MouseEvent> {
    Callback::from(move |_| {
        nav.back();
    })
}

#[function_component(NotFound)]
pub fn main() -> Html {
    html! {
        <>
            <Title />
            <p>{ "Not found.." }</p>
            <GoBack />
        </>
    }
}
