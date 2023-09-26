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
    extend: {},
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
