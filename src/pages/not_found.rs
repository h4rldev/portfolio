use crate::RootRoute;
use yew::prelude::*;
use yew_router::prelude::*;

#[function_component(Title)]
pub fn title() -> Html {
    html! {
        <h1>{ "404" }</h1>
    }
}

#[function_component(Bottom)]
pub fn bottom() -> Html {
    let navigator = use_navigator().unwrap();
    let onclick = Callback::from(move |_| {
        navigator.replace(&RootRoute::Index);
    });
    html! {

        <footer>
            { "Go back to " } <a href="" target="_self" {onclick}>{ "Home" }</a> { "?"}
        </footer>
    }
}

#[function_component(NotFound)]
pub fn main() -> Html {
    html! {
        <>
            <Title />
            <p>{ "Not found.." }</p>
            <Bottom />
        </>
    }
}
