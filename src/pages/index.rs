use crate::GoTo;
use yew::prelude::*;

#[function_component(Title)]
pub fn title() -> Html {
    html! {
        <h1 class="font-medium text-xl subpixel-antialiased items-center text-center">{ "H4rl's Site" }</h1>
    }
}

#[function_component(Index)]
pub fn main() -> Html {
    html! {
        <>
            <Title />
            <GoTo route={String::from("About")} message={(String::from(""), String::from(""))} /> <br />
            <GoTo route={String::from("Blog")} message={(String::from(""), String::from(""))} /> <br />
            <GoTo route={String::from("???")} message={(String::from(""), String::from(""))} />
        </>
    }
}
