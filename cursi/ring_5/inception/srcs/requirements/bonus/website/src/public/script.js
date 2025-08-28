document.addEventListener("DOMContentLoaded", () => {
  const hours = new Date().getHours();
  const greeting =
    hours < 12 ? "Good morning ☀️" :
    hours < 18 ? "Good afternoon 🌤️" :
                 "Good evening 🌙";

  const login = window.RUNTIME_CONFIG?.LOGIN || "guest";

  const headerTitle = document.getElementById("greeting-title");
  const headerSubtitle = document.getElementById("greeting-subtitle");
  headerTitle.textContent = `Hello, I'm Sebastian Villa 👋`;
  headerSubtitle.textContent = `${greeting} ${login} — Welcome to my website`;

  const splash = document.getElementById("splash");
  const main = document.getElementById("main-content");

  setTimeout(() => {
    splash.classList.add("hidden");
  }, 3000);

  splash.addEventListener("transitionend", (e) => {
    if (e.propertyName !== "opacity") return;
    splash.style.display = "none";
    main.classList.add("block");
  }, { once: true });
});