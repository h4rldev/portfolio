use crate::GoBack;
use yew::prelude::*;

#[function_component(Title)]
pub fn title() -> Html {
    html! {
        <h1>{ "Blog" }</h1>
    }
}

#[function_component(Blog)]
pub fn main() -> Html {
    html! {
        <>
            <Title />
            <p>{ "This is the blog page." }</p>
            <GoBack />
        </>
    }
}
