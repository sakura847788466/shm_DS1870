/* eslint-env mozilla/frame-script */

let {classes: Cc, interfaces: Ci, results: Cr, utils: Cu} = Components;

Cu.import("resource://gre/modules/XPCOMUtils.jsm");
XPCOMUtils.defineLazyModuleGetter(this, "Services",
  "resource://gre/modules/Services.jsm");

let mozCNErrorPage = {
  init() {
    Services.obs.addObserver(this, "content-document-global-created");
    addEventListener("unload", () => {
      Services.obs.removeObserver(this, "content-document-global-created");
    });
  },

  observe(subject, topic, data) {
    switch (topic) {
      case "content-document-global-created":
        if (!content || !subject ||
            subject.top !== content || subject.top !== subject) {
          return;
        }
        if (!content.document.documentURI.startsWith("about:neterror?")) {
          return;
        }
        content.document.addEventListener("DOMContentLoaded", this);
        break;
    }
  },

  handleEvent(evt) {
    switch (evt.type) {
      case "DOMContentLoaded":
        this.patchErrorPage(evt);
        break;
      default:
        break;
    }
  },

  patchErrorPage(event) {
    var contentDoc = event.target;
    var contentWin = contentDoc.defaultView;

    var errorPageBody = contentDoc.body;

    // Add 'Go To Homepage' button
    var btnChildren = (contentDoc.querySelector("#netErrorButtonContainer > button") ||
                       contentDoc.querySelector("#errorPageContainer > button"));
    if (btnChildren && btnChildren.style.display !== "none") {
      var goToHomePageBtn = contentDoc.createElement("button");
      goToHomePageBtn.id = "goToHomePage";
      goToHomePageBtn.textContent = Services.strings.
        createBundle("chrome://ceerrorpage/locale/overlay.properties").
        GetStringFromName("goToHomePage");
      goToHomePageBtn.addEventListener("click", () => {
        contentWin.location = "http://home.firefoxchina.cn/?from_err_btn";
      });
      btnChildren.parentNode.insertBefore(goToHomePageBtn, btnChildren);
    }

    // Reset the default error page css
    var domWindowUtils = contentWin.QueryInterface(Ci.nsIInterfaceRequestor).
      getInterface(Ci.nsIDOMWindowUtils);
    var cssUri = Services.io.newURI("chrome://ceerrorpage/skin/overlay.css");
    domWindowUtils.loadSheet(cssUri, Ci.nsIDOMWindowUtils.AUTHOR_SHEET);

    // Add site recomandation iframe to the default error page
    if (content.navigator.onLine) {
      var recomendIframe = contentDoc.createElement("iframe");
      recomendIframe.id = "recomendIframe";
      recomendIframe.height = "0px";
      errorPageBody.appendChild(recomendIframe);
      recomendIframe.src = "http://newtab.firefoxchina.cn/error-tab-rec.html";
      recomendIframe.addEventListener("load", () => {
        if (recomendIframe.contentWindow.document.URL.match(/^about:neterror/)) {
          errorPageBody.removeChild(recomendIframe);
        } else {
          recomendIframe.height = "330px";
        }
      });
      var timer = 0;
      var interval = contentWin.setInterval(() => {
        if (timer < 150 && recomendIframe.contentDocument) {
          if (recomendIframe.contentDocument.readyState == "complete" ||
              recomendIframe.contentDocument.readyState == "interactive") {
            if (recomendIframe.contentWindow.document.URL.match(/^about:neterror/)) {
              errorPageBody.removeChild(recomendIframe);
            } else {
              recomendIframe.height = "330px";
            }
            timer = 0;
            contentWin.clearInterval(interval);
          } else {
            timer++;
          }
        } else {
          timer = 0;
          contentWin.clearInterval(interval);
        }
      }, 200);
    }
  }
}
mozCNErrorPage.init();
