use super::router::Route;
use chrono::{DateTime, Utc};
use gloo_timers::callback::Interval;
use yew_router::prelude::*;

use yew::prelude::*;

#[function_component(Age)]
pub fn age() -> Html {
    let age = use_state(calculate_age);

    let age_for_effect = age.clone();
    use_effect(move || {
        let age = age.clone();
        let interval = Interval::new(1, move || {
            age.set(calculate_age());
        });

        interval.forget();

        || {}
    });

    let age_for_render = age_for_effect;
    html! {
        <span class="text-puccin-teal age"> { format!("{:.15}", *age_for_render) } </span>
    }
}

fn calculate_age() -> f64 {
    let birthday = DateTime::parse_from_rfc2822("Fri, 2 Sep 2005 00:00:00 +0100").unwrap();
    let now = Utc::now();
    let age_seconds = now.timestamp() - birthday.timestamp();
    age_seconds as f64 / 60.0 / 60.0 / 24.0 / 365.0
}

#[derive(Properties, Clone, PartialEq, Eq)]
pub struct ButtonProps {
    #[prop_or("".to_string())]
    pub alt: String,
    #[prop_or_default]
    pub text: String,
    #[prop_or("".to_string())]
    pub href: String,
    #[prop_or_default]
    pub icon_class: String,
}

#[function_component(Button)]
pub fn button(props: &ButtonProps) -> Html {
    let navigator = use_navigator().expect("Navigator not found");
    let button_props = props.clone();

    let onclick =
        Callback::from(move |_| navigator.push(&Route::recognize(&button_props.href).unwrap()));

    html! {
        <button
            class="buttonwithicon"
            onclick={onclick}
        >
            <i
                class={classes!("buttonicon", {button_props.icon_class})}
                alt={button_props.alt}
            />
            { button_props.text }
        </button>
    }
}
