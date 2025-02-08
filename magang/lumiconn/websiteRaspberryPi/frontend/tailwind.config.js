const flowbite = require("flowbite-react/tailwind");

module.exports = {
  darkMode: 'class',
  content: [
    "./index.html", 
    "./src/**/*.{js,ts,jsx,tsx}",
    flowbite.content(),
  ],
  theme: {
    extend: {
      colors: {
        primary: '#1D4ED8',
        secondary: '#6366F1',
      },
      fontFamily: {
        sans: ['Inter', 'sans-serif'],
      },
    },
  },
  plugins: [
    flowbite.plugin(),
  ],
};

