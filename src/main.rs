use catppuccin::Flavour::Mocha;
use pages::{blog::Blog, contact::Contact, index::Index, not_found::NotFound};
use std::fmt;
use yew::prelude::*;
use yew::Renderer;
use yew_router::prelude::*;

mod pages;

#[derive(Routable, PartialEq, Eq, Clone)]
pub enum Route {
    #[at("/")]
    Index,
    #[at("/contact")]
    Contact,
    #[at("/blog")]
    Blog,
    #[not_found]
    #[at("/404")]
    NotFound,
}

impl fmt::Display for Route {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        match self {
            Route::Index => write!(f, "Home"),
            Route::Contact => write!(f, "Contact"),
            Route::Blog => write!(f, "Blog"),
            Route::NotFound => write!(f, "404"),
        }
    }
}

const ROOT_STYLE: &str = "min-h-screen bg-puccin-base text-white";

fn switch(routes: Route) -> Html {
    match routes {
        Route::Index => html! { <Index /> },
        Route::Contact => html! { <Contact />  },
        Route::NotFound => html! { <NotFound /> },
        Route::Blog => html! { <Blog /> },
    }
}

#[function_component(Nav)]
pub fn nav() -> Html {
    let li_style = "inline-flex px-3";
    let title_style = "inline-flex px-3";
    let title = html! {
        <h1 class="font-medium text-xl subpixel-antialiased items-center text-left">
            <GoTo route={String::from("Home")} route_nickname={String::from("h4rl")} button_style={String::from("cursor-pointer")}/>
        </h1>
    };
    let arrow = "px-0 inline-flex";
    let hr_style = "border-b-2 border-teal-200";
    let sticky = "font-mono sticky";
    html! {
        <nav class={sticky}>
            <ul class="py-2 select-none">
                <li class={title_style}>{title}</li>
                <li class={arrow}>{"=>"}</li>
                <li class={li_style}><GoTo route={String::from("Contact")} /></li>
                <li class={li_style}><GoTo route={String::from("Blog")} /></li>
            </ul>
            <hr class={hr_style}/>
        </nav>
    }
}

#[derive(Properties, Clone, PartialEq, Eq)]
pub struct MetaContent {
    #[prop_or("H4rl".to_string())]
    pub meta_title: String,
    #[prop_or("Website".to_string())]
    pub meta_type: String,
    #[prop_or("https://h4rl-is-def.me".to_string())]
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
    html! {
        <head>
            <meta property="og:title" content={metadata.meta_title} />
            <meta property="og:type" content={metadata.meta_type} />
            <meta property="og:url" content={metadata.meta_url} />
            <meta property="og:image" content={metadata.meta_image} />
            <meta
              property="og:description"
              content={metadata.meta_description}
            />
            <meta name="theme-color" content={metadata.theme_color} />
            <meta name="twitter:card" content={metadata.twitter_card} />
            <meta name="twitter:site" content={metadata.twitter_site} />
            <meta name="twitter:creator" content={metadata.twitter_creator} />
            <title>{ metadata.title }</title>
        </head>
    }
}

#[derive(Properties, Clone, PartialEq, Eq)]
pub struct GoToProps {
    #[prop_or(Route::Index.to_string())]
    pub route: String,
    #[prop_or(String::from(""))]
    pub route_nickname: String,
    #[prop_or(String::from("hover:text-teal-200 cursor-pointer"))]
    pub button_style: String,
    #[prop_or((String::from(""), String::from("")))]
    pub message: (String, String),
}

#[function_component(GoTo)]
fn goto(props: &GoToProps) -> Html {
    let message: (String, String) = props.message.clone();
    let navigator = use_navigator().unwrap();
    let route = match props.route.as_str() {
        "Index" | "Home" => Route::Index,
        "Contact" => Route::Contact,
        "Blog" => Route::Blog,
        _ => Route::NotFound,
    };
    let onclick = Callback::from(move |_| {
        navigator.push(&route);
    });
    if props.route_nickname.is_empty() {
        html! {
            <>
                { message.0 }
                <a target="_self" {onclick} class={&props.button_style}>{ &props.route }</a>
                { message.1 }
            </>
        }
    } else {
        html! {
            <>
                { message.0 }
                <a target="_self" {onclick} class={&props.button_style}>{ &props.route_nickname }</a>
                { message.1 }
            </>
        }
    }
}

#[function_component(App)]
fn app() -> Html {
    html! {
        <html class={ROOT_STYLE}>
            <BrowserRouter>
                <Switch<Route> render={switch} />
            </BrowserRouter>
        </html>
    }
}

fn main() {
    Renderer::<App>::new().render();
}
