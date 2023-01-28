const loadEmscriptenModule = () => {
  window.Module = {
    preRun: [],
    postRun: [],
    onAbort: (msg) => console.error(msg)
  };

  return new Promise((resolve, reject) => {
    const script = document.createElement('script');
    document.body.appendChild(script);

    script.src = './sattract.js';
    script.async = true;
    script.onload = () => {
      console.log('Script loaded.');
      if (window.sattract) {
        window.sattract().then((sattractModule) => {
          resolve(sattractModule);
        });
      } else {
        reject('An error occurred attempting to load the emscripten engine.');
      }
    };
  });
}

const start = async () => {
  const module = await loadEmscriptenModule();
  const screen = document.getElementById("screen");
  module.canvas = screen;
  module._main();

  addEventListener("resize", () => {
    const rect = screen.getBoundingClientRect();
    console.log(rect.width + ", " + rect.height)
    module._setWindowSize(rect.width | 0, rect.height | 0);
  });


  const FPS = 1000 / 60;

  // TODO: Use request animation frame
  setInterval(() => {
    module._main_loop();
  }, FPS);
}

start();
