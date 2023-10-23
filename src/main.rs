use catppuccin::Flavour::Mocha;
use pages::{index::Index, not_found::NotFound};
use std::fmt;
use web_sys::window;
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
        _ => html! { <NotFound /> },
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

fn create_meta_tag(
    document: &web_sys::Document,
    property: &str,
    content: &str,
) -> web_sys::Element {
    let meta_tag = document
        .create_element("meta")
        .expect("Failed to create meta tag element");
    meta_tag
        .set_attribute("property", property)
        .expect("Failed to set attribute for property");
    meta_tag
        .set_attribute("content", content)
        .expect("Failed to set attribute for content");
    meta_tag
}

#[function_component(Meta)]
pub fn meta(meta_content: &MetaContent) -> Html {
    let metadata = meta_content;
    let document = window()
        .expect("Failed to get window")
        .document()
        .expect("Failed to get document");
    let head = document.head().expect("Failed to get head");

    let meta_title = create_meta_tag(&document, "og:title", &metadata.meta_title);
    let meta_type = create_meta_tag(&document, "og:type", &metadata.meta_type);
    let meta_url = create_meta_tag(&document, "og:url", &metadata.meta_url);
    let meta_image = create_meta_tag(&document, "og:image", &metadata.meta_image);
    let meta_description = create_meta_tag(&document, "og:description", &metadata.meta_description);
    let meta_theme_color = create_meta_tag(&document, "theme-color", &metadata.theme_color);
    let meta_twitter_card = create_meta_tag(&document, "twitter:card", &metadata.twitter_card);
    let meta_twitter_site = create_meta_tag(&document, "twitter:site", &metadata.twitter_site);
    let meta_twitter_creator =
        create_meta_tag(&document, "twitter:creator", &metadata.twitter_creator);
    let title = document
        .create_element("title")
        .expect("Failed to create title element");
    title.set_inner_html(&metadata.title);

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
        title,
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
        <html class="relative min-h-screen text-puccin-text text-lg overflow-hidden">
        <div class="absolute inset-0 bg-evening bg-cover bg-center blur-lg scale-110 overflow-hidden"></div>
            <BrowserRouter>
                <Switch<Route> render={switch} />
            </BrowserRouter>
        </html>
    }
}

fn main() {
    Renderer::<App>::new().render();
}
