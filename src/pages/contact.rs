use crate::Nav;
use yew::prelude::*;

#[function_component(Title)]
pub fn title() -> Html {
    html! {
        <h1>{ "Contact" }</h1>
    }
}

/*#[function_component(Bottom)]
pub fn bottom() -> Html {
    html! {
        <footer>{ "This is the bottom of the about page." }</footer>
    }
}*/

#[function_component(Contact)]
pub fn main() -> Html {
    html! {
        <>
            <Nav/>
            <Title />
            <p class="text-2xl px-10">{ "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum." }</p>
        </>
    }
}
