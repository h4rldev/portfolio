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
        evening: 'url("evening-sky.png")',
        sweden: 'url("sweden.gif")',
      },
      animation: {
        expand: "expand 2s ease-in-out",
      },
      keyframes: {
        expand: {
          "0%": { transform: "scale(0)" },
          "100%": { transform: "scale(1)", width: "100vw", height: "100vh" },
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
      },
      height: {
        65: "65px",
        75: "75px",
        screen: "100vh",
        112: "28rem",
        192: "48rem",
        256: "64rem",
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
  ],
};
