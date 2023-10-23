module.exports = {
  mode: "jit",
  content: {
    files: ["src/**/*.rs", "index.html"],
  },
  darkMode: "media", // 'media' or 'class'
  theme: {
    fontFamily: {
      mono: ["FiraCode Nerd Font Mono", "monospace"],
      ubuntu: ["Ubuntu Nerd Font Propo", "sans-serif"],
      tahoma: ["Tahoma", "sans-serif"],
    },
    extend: {
      backgroundImage: {
        evening: 'url("evening-sky.png")',
      },
      width: {
        65: "65px",
        75: "75px",
      },
      height: {
        65: "65px",
        75: "75px",
      },
    },
  },
  variants: {
    extend: {},
  },
  plugins: [
    require("@catppuccin/tailwindcss")({
      prefix: "puccin",
      defaultFlavour: "mocha",
    }),
  ],
};
