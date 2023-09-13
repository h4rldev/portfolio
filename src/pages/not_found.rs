use crate::GoTo;
use yew::prelude::*;

#[function_component(Title)]
pub fn title() -> Html {
    html! {
        <h1>{ "404" }</h1>
    }
}

#[function_component(NotFound)]
pub fn main() -> Html {
    html! {
        <>
            <Title />
            <p>{ "Not found.." }</p>
            <GoTo />
        </>
    }
}
