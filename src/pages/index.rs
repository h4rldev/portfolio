use crate::GoTo;
use yew::prelude::*;

#[function_component(Title)]
pub fn title() -> Html {
    html! {
        <h1 class="font-medium text-xl subpixel-antialiased">{ "H4rl's Site" }</h1>
    }
}

#[function_component(Index)]
pub fn main() -> Html {
    html! {
        <>
            <Title />
            <GoTo route={String::from("About")} /> <br />
            <GoTo route={String::from("Blog")} /> <br />
            <GoTo route={String::from("asdljuasdkjhaskdgj")} />
        </>
    }
}
