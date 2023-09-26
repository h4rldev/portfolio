use crate::Nav;
use yew::prelude::*;

#[function_component(Index)]
pub fn main() -> Html {
    html! {
        <>
            <Nav/>
            <Title />
        </>
    }
}

#[function_component(Title)]
pub fn title() -> Html {
    html! {
        <h1>{ "Home" }</h1>
    }
}
