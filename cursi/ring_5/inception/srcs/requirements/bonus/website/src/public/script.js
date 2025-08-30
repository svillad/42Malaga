document.addEventListener("DOMContentLoaded", () => {
  const hours = new Date().getHours();
  const greeting =
    hours < 12 ? "Good morning ☀️" :
    hours < 18 ? "Good afternoon 🌤️" :
                 "Good evening 🌙";

  const login = window.RUNTIME_CONFIG?.LOGIN || "guest";

  const headerTitle = document.getElementById("greeting-title");
  const headerSubtitle = document.getElementById("greeting-subtitle");
  headerTitle.textContent = `${greeting} ${login}`;
  headerSubtitle.textContent = `I'm Sebastian Villa 👋`;

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