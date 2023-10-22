use chrono::{DateTime, Utc};
use gloo_timers;
use gloo_timers::callback::Interval;
use yew::functional::*;
use yew::prelude::*;

#[function_component(Index)]
pub fn main() -> Html {
    html! {
        <div class="relative flex h-screen overflow-hidden">
            <div class="font-mono m-auto bg-puccin-base p-16 rounded-3xl overflow-hidden">
                <Title />
                <Description />
            </div>
        </div>
    }
}

#[function_component(Age)]
pub fn age() -> Html {
    let age = use_state(|| calculate_age());

    let age_for_effect = age.clone();
    use_effect(move || {
        let age = age.clone();
        let interval = Interval::new(0, move || {
            age.set(calculate_age());
        });

        interval.forget();

        || {}
    });

    let age_for_render = age_for_effect;
    html! {
        <span class="text-puccin-teal overflow-hidden"> { *age_for_render } </span>
    }
}

fn calculate_age() -> f32 {
    let birthday = DateTime::parse_from_rfc2822("Fri, 2 Sep 2005 00:00:00 +0100").unwrap();
    let now = Utc::now();
    let age_seconds = now.timestamp() - birthday.timestamp();
    let age_years = age_seconds as f32 / 60.0 / 60.0 / 24.0 / 365.0;
    age_years
}

#[function_component(Description)]
pub fn description() -> Html {
    html! {
        <>
            <p> { "I'm an aspiring:" } </p>
            <div class="text-center">
                <ul class="inline-block list-disc text-left">
                    <li> <p class="text-puccin-red"> { "Software Engineer" } </p> </li>
                    <li> <p class="text-puccin-red"> { "Computer Technician" } </p> </li>
                    <li> <p class="text-puccin-red"> { "Network Technician" } </p> </li>
                    <li> <p class="text-puccin-red"> { "Game Developer" } </p> </li>
                    <li> <p class="text-puccin-red"> { "System Administrator" } </p> </li>
                </ul>
            </div>
        </>
    }
}

#[function_component(Title)]
pub fn title() -> Html {
    html! {
        <>
            <p class="text-2xl/loose"> { "Hey, I'm " } <span class="text-puccin-teal"> { "H4rl" } </span> </p>
            <p class="text-sm mb-7"> <Age/> { " years old" }</p>
        </>

    }
}
