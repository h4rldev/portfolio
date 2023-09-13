use crate::GoTo;
use yew::prelude::*;

#[function_component(Title)]
pub fn title() -> Html {
    html! {
        <h1>{ "About" }</h1>
    }
}

/*#[function_component(Bottom)]
pub fn bottom() -> Html {
    html! {
        <footer>{ "This is the bottom of the about page." }</footer>
    }
}*/

#[function_component(About)]
pub fn main() -> Html {
    html! {
        <>
            <Title />
            <p>{ "This is the about page." }</p>
            <GoTo />
        </>
    }
}
