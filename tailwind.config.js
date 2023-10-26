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
      width: {
        65: "65px",
        75: "75px",
      },
      height: {
        65: "65px",
        75: "75px",
      },
      listStyleType: {
        square: "square",
      },
    },
  },
  variants: {},
  plugins: [
    require("@catppuccin/tailwindcss")({
      prefix: "puccin",
      defaultFlavour: "mocha",
    }),
  ],
};
