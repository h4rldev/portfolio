use catppuccin::Flavour::Mocha;
use pages::{index::Index, not_found::NotFound};
use std::fmt;
use wasm_bindgen::JsCast;
use web_sys::{window, HtmlHeadElement};
use yew::prelude::*;
use yew::Renderer;
use yew_router::prelude::*;
mod pages;

#[derive(Routable, PartialEq, Eq, Clone)]
pub enum Route {
    #[at("/")]
    Index,
    #[not_found]
    #[at("/404")]
    NotFound,
}

impl fmt::Display for Route {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        match self {
            Route::Index => write!(f, "Home"),
            Route::NotFound => write!(f, "404"),
        }
    }
}

fn switch(routes: Route) -> Html {
    match routes {
        Route::Index => html! { <Index /> },
        Route::NotFound => html! { <NotFound /> },
    }
}

#[derive(Properties, Clone, PartialEq, Eq)]
pub struct MetaContent {
    #[prop_or("H4rl".to_string())]
    pub meta_title: String,
    #[prop_or("Website".to_string())]
    pub meta_type: String,
    #[prop_or(window().expect("Failed to get window").location().href().expect("Failed to get href"))]
    pub meta_url: String,
    #[prop_or("img/panko2.jpeg".to_string())]
    pub meta_image: String,
    #[prop_or("H4rl's Site. Currently In Development. Sorry.".to_string())]
    pub meta_description: String,
    #[prop_or(Mocha.teal().hex())]
    pub theme_color: String,
    #[prop_or("summary".to_string())]
    pub twitter_card: String,
    #[prop_or("@h4rl3h".to_string())]
    pub twitter_site: String,
    #[prop_or("@h4rl3h".to_string())]
    pub twitter_creator: String,
    #[prop_or("H4rl".to_string())]
    pub title: String,
}

#[function_component(Meta)]
pub fn meta(meta_content: &MetaContent) -> Html {
    let metadata = meta_content.clone();
    /*if window()
        .expect("Failed to get window")
        .location()
        .href()
        .expect("Failed to get href")
        != "https://h4rl-is-def.me/"
    {
        html! {
            <head>
                <meta property="og:title" content="Error 404" />
                <meta property="og:type" content={metadata.meta_type} />
                <meta property="og:url" content={metadata.meta_url} />
                <meta property="og:image" content="https://http.cat/404" />
                <meta
                  property="og:description"
                  content="Not Found"
                />
                <meta name="theme-color" content={metadata.theme_color} />
                <meta name="twitter:card" content={metadata.twitter_card} />
                <meta name="twitter:site" content={metadata.twitter_site} />
                <meta name="twitter:creator" content={metadata.twitter_creator} />
                <title>{ metadata.title }</title>
            </head>
        }
    } else {
        html! {
            <head>
                <meta property="og:title" content={metadata.meta_title} />
                <meta property="og:type" content={metadata.meta_type} />
                <meta property="og:url" content={metadata.meta_url} />
                <meta property="og:image" content={metadata.meta_image} />
                <meta
                  property="og:description"
                  content="H4rl's Site. Currently In Development. Sorry."
                />
                <meta name="theme-color" content={metadata.theme_color} />
                <meta name="twitter:card" content={metadata.twitter_card} />
                <meta name="twitter:site" content={metadata.twitter_site} />
                <meta name="twitter:creator" content={metadata.twitter_creator} />
                <title>{ metadata.title }</title>
            </head>
        }
    }*/
    let document = window()
        .unwrap()
        .document()
        .expect("Failed to get document");
    let head = document.head().expect("Failed to get head");

    let meta_title = document
        .create_element("meta")
        .expect("Failed to create meta title element");
    meta_title
        .set_attribute("property", "og:title")
        .expect("Failed to set attribute for title property");
    meta_title
        .set_attribute("content", &metadata.meta_title)
        .expect("Failed to set attribute for title content");

    let meta_type = document
        .create_element("meta")
        .expect("Failed to create meta type element");
    meta_type
        .set_attribute("property", "og:type")
        .expect("Failed to set attribute for type property");
    meta_type
        .set_attribute("content", &metadata.meta_type)
        .expect("Failed to set attribute for type content");

    let meta_url = document
        .create_element("meta")
        .expect("Failed to create meta url element");
    meta_url
        .set_attribute("property", "og:url")
        .expect("Failed to set attribute for url property");
    meta_url
        .set_attribute("content", &metadata.meta_url)
        .expect("Failed to set attribute for url content");

    let meta_image = document
        .create_element("meta")
        .expect("Failed to create meta image element");
    meta_image
        .set_attribute("property", "og:image")
        .expect("Failed to set attribute for image property");
    meta_image
        .set_attribute("content", &metadata.meta_image)
        .expect("Failed to set attribute for image content");

    let meta_description = document
        .create_element("meta")
        .expect("Failed to create meta description element");
    meta_description
        .set_attribute("property", "og:description")
        .expect("Failed to set attribute for description property");
    meta_description
        .set_attribute("content", &metadata.meta_description)
        .expect("Failed to set attribute for description content");

    let meta_theme_color = document
        .create_element("meta")
        .expect("Failed to create meta theme color element");
    meta_theme_color
        .set_attribute("name", "theme-color")
        .expect("Failed to set attribute for theme color name");
    meta_theme_color
        .set_attribute("content", &metadata.theme_color)
        .expect("Failed to set attribute for theme color content");

    let meta_twitter_card = document
        .create_element("meta")
        .expect("Failed to create meta twitter card element");
    meta_twitter_card
        .set_attribute("name", "twitter:card")
        .expect("Failed to set attribute for twitter card name");
    meta_twitter_card
        .set_attribute("content", &metadata.twitter_card)
        .expect("Failed to set attribute for twitter card content");

    let meta_twitter_site = document
        .create_element("meta")
        .expect("Failed to create meta twitter site element");
    meta_twitter_site
        .set_attribute("name", "twitter:site")
        .expect("Failed to set attribute for twitter site name");
    meta_twitter_site
        .set_attribute("content", &metadata.twitter_site)
        .expect("Failed to set attribute for twitter site content");

    let meta_twitter_creator = document
        .create_element("meta")
        .expect("Failed to create meta twitter creator element");
    meta_twitter_creator
        .set_attribute("name", "twitter:creator")
        .expect("Failed to set attribute for twitter creator name");
    meta_twitter_creator
        .set_attribute("content", &metadata.twitter_creator)
        .expect("Failed to set attribute for twitter creator content");

    let tags = [
        meta_title,
        meta_type,
        meta_url,
        meta_image,
        meta_description,
        meta_theme_color,
        meta_twitter_card,
        meta_twitter_site,
        meta_twitter_creator,
    ];

    for tag in tags.iter() {
        head.append_child(tag).expect("Failed to append child");
    }

    html! {}
}

#[derive(Properties, Clone, PartialEq, Eq)]
pub struct GoToProps {
    #[prop_or(Route::Index.to_string())]
    pub route: String,
    #[prop_or(String::from(""))]
    pub route_nickname: String,
    #[prop_or(String::from("hover:text-puccin-teal cursor-pointer font-mono"))]
    pub class: String,
    #[prop_or((String::from(""), String::from("")))]
    pub message: (String, String),
}

#[function_component(GoTo)]
fn goto(props: &GoToProps) -> Html {
    let message: (String, String) = props.message.clone();
    let navigator = use_navigator().unwrap();
    let route = match props.route.as_str() {
        "Index" | "Home" => Route::Index,
        _ => Route::NotFound,
    };
    let onclick = Callback::from(move |_| {
        navigator.push(&route);
    });
    if props.route_nickname.is_empty() {
        html! {
            <>
                { message.0 }
                <a target="_self" {onclick} class={&props.class}>{ &props.route }</a>
                { message.1 }
            </>
        }
    } else {
        html! {
            <>
                { message.0 }
                <a target="_self" {onclick} class={&props.class}>{ &props.route_nickname }</a>
                { message.1 }
            </>
        }
    }
}

#[function_component(App)]
fn app() -> Html {
    html! {
        <>
        <Meta />
        <html class="relative min-h-screen text-puccin-text text-lg overflow-hidden">
        <div class="absolute inset-0 bg-evening bg-cover bg-center blur-lg scale-110 overflow-hidden"></div>
            <BrowserRouter>
                <Switch<Route> render={switch} />
            </BrowserRouter>
        </html>
        </>
    }
}

fn main() {
    Renderer::<App>::new().render();
}
