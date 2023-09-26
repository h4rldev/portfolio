use crate::Nav;
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
            <Nav/>
            <Title />
            <p>{ "Not found.." }</p>
        </>
    }
}
