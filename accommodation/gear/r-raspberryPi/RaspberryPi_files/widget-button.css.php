/* <style> */

#telegramim_fixed {
position: fixed;
z-index: 999999999;
font-size: 16px;
letter-spacing: normal;
}

.telegramim_button {
opacity: 1;
cursor: pointer;
text-align: center;
display: block;
padding: 10px;
text-decoration: none !important;
text-transform: none;
letter-spacing: normal;
}



.telegramim_button span {
text-decoration: none;
text-transform: none;
letter-spacing: normal;
}


.telegramim_button small {
 font-size: 70%;
 display: block;
 padding: 1px 5px;
 background: transparent;
 text-align: center;
 }


#telegramim_fixed.rightbottom {
right: 2%;
bottom: 2%;
}

.telegramim_shadow {
box-shadow: 1px 1px 5px rgba(0,0,0,0.5);
}

.telegramim_shadow:hover {
box-shadow: 1px 1px 15px rgba(0,0,0,0.5) !important;
}



.telegramim_pulse {
  animation: animationpulse 2s infinite;
   -webkit-animation: animationpulse 2s ease-out;
   -webkit-animation-iteration-count: infinite;
}
.telegramim_pulse:hover {
  animation: linear;
}

@-webkit-keyframes animationpulse {
  0% {
    -webkit-box-shadow: 0 0 0 0 inherit;
  }
  70% {
      -webkit-box-shadow: 0 0 0 15px rgba(0,0,0, 0);
  }
  100% {
      -webkit-box-shadow: 0 0 0 0 rgba(0,0,0, 0);
  }
}
@keyframes animationpulse {
  0% {
     transform: scale(1.0, 1.0);
    -moz-box-shadow: 0 0 0 0 inherit;
    box-shadow: 0 0 0 0 inherit;
  }
  10% {
     transform: scale(1.1, 1.1);
  }
  15% {
     transform: scale(1.0, 1.0);
  }
  70% {
      -moz-box-shadow: 0 0 0 15px rgba(0,0,0, 0);
      box-shadow: 0 0 0 15px rgba(0,0,0, 0);
  }
  100% {
      -moz-box-shadow: 0 0 0 0 rgba(0,0,0, 0);
      box-shadow: 0 0 0 0 rgba(0,0,0, 0);
  }
}
@-ms-keyframes animationpulse {
    0% {
        -ms-transform: scale(1.0, 1.0);
    }
    10% {
        -ms-transform: scale(1.1, 1.1);
    }
    20% {
        -ms-transform: scale(1.0, 1.0);
    }
    100% {
       -ms-transform: scale(1.0, 1.0);
    }
}