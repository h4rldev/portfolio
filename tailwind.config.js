const { addDynamicIconSelectors } = require("@iconify/tailwind");
module.exports = {
  mode: "jit",
  content: {
    files: ["src/**/*.rs", "index.html"],
  },
  darkMode: "media", // 'media' or 'class'
  theme: {
    fontFamily: {
      mono: ["FiraCode Nerd Font Mono", "monospace"],
    },
    extend: {
      fontFamily: {
        ubuntu: ["Ubuntu Nerd Font Propo", "sans-serif"],
        tahoma: ["Tahoma", "sans-serif"],
      },
      backgroundImage: {
        evening: 'url("img/bg/evening-sky.png")',
        sweden: 'url("img/other_assets/sweden.gif")',
      },
      animation: {
        expand: "expand 2s ease-in-out",
        fadein: "fadein 2s ease-in-out",
      },
      keyframes: {
        expand: {
          "0%": { transform: "scale(0)" },
          "100%": { transform: "scale(1)", width: "100vw", height: "100vh" },
        },
        fadein: {
          "0%": { opacity: "0" },
          "100%": { opacity: "1" },
        },
      },
      transitionProperty: {
        width: "width",
        height: "height",
        spacing: "margin, padding",
        transform: "transform",
      },
      width: {
        65: "65px",
        75: "75px",
        112: "28rem",
        192: "48rem",
        256: "64rem",
        "1/7": "14.285714285714286%",
        "2/7": "28.571428571428573%",
        "3/7": "42.857142857142859%",
        "4/7": "57.142857142857145%",
        "5/7": "71.428571428571431%",
        "6/7": "85.714285714285717%",
        "7/7": "100%",
        "1/8": "12.5%",
        "2/8": "25%",
        "3/8": "37.5%",
        "4/8": "50%",
        "5/8": "62.5%",
        "6/8": "75%",
        "7/8": "87.5%",
        "8/8": "100%",
      },
      height: {
        65: "65px",
        75: "75px",
        screen: "100vh",
        112: "28rem",
        192: "48rem",
        256: "64rem",
        "1/7": "14.285714285714286%",
        "2/7": "28.571428571428573%",
        "3/7": "42.857142857142859%",
        "4/7": "57.142857142857145%",
        "5/7": "71.428571428571431%",
        "6/7": "85.714285714285717%",
        "7/7": "100%",
        "1/8": "12.5%",
        "2/8": "25%",
        "3/8": "37.5%",
        "4/8": "50%",
        "5/8": "62.5%",
        "6/8": "75%",
        "7/8": "87.5%",
        "8/8": "100%",
      },
      borderRadius: {
        "4xl": "2rem",
      },
      listStyleType: {
        square: "square",
      },
    },
  },
  variants: {
    transitionProperty: ["responsive", "motion-safe", "motion-reduce"],
    transitionDuration: ["responsive"],
  },
  plugins: [
    require("@catppuccin/tailwindcss")({
      prefix: "puccin",
      defaultFlavour: "mocha",
    }),
    addDynamicIconSelectors({
      prefix: "i",
    }),
    addDynamicIconSelectors({
      prefix: "i-hover",
      overrideOnly: true,
    }),
  ],
};
