import './main.scss';
import pcbImage from './img/pcb.png';
import { diffTrimmedLines } from 'diff';


fetch( '/ssid_list' )
  .then( response => response.json() )
  .then( data => {
    displaySSIDList( ' *' + data.join( ' *' ) );
  } );

// Swap above fetch with below mock for local testing
/*
setTimeout( () => {
  const data = [
      "sbv2b_iot",
      "sbv2b_lan_2.4ghz",
      "vs-0a84fc",
      "Altibox951496",
      "sbv2b_iot_g_2.4ghz",
      "sbv2b_g_2.4ghz",
      "Fjordveien5",
      "Altibox102746",
      "Steinsbyveien7",
      "Hildepilde"
  ];
  displaySSIDList( ' *' + data.join( ' *' ) );
}, 500 );
*/

document.querySelector( '#espen50 img.pcb' ).setAttribute( 'src', pcbImage );
document.getElementById( 'espen50' ).classList.remove( 'hide' );

let ts = 0;
let itemId = 0;
let typeBuffer = "";
let ssid = null;

const terminal = document.getElementById( 'terminal' );

function onSSIDSelect( itemId, selected_ssid ) {
  ssid = selected_ssid;
  promptSSIDPassword();
}

const handleUserInput = ( e ) => {
  switch( e.key ) {
    case 'ArrowLeft': // fallthrough
    case 'ArrowRight':
      e.preventDefault();
      break;      
    case 'Enter':
      e.preventDefault();
      e.target.classList.remove( 'prompt' );
      e.target.classList.add( 'complete' );
      e.target.removeEventListener( 'keydown', handleUserInput );
      e.target.setAttribute( 'contenteditable', 'false' );
      const password = e.target.innerHTML;
      fetch( '/ssid_auth', {
        method: 'POST',
        headers: {
          'Content-Type': 'application/json'
        },
        body: JSON.stringify( { ssid, password } )
      } )
        .then( response => response.json() )
        .then( data => {
          if( data.status === 'ok' ) {
            displayAuthSendOK();
          }
          else {
            displayAuthSendError();
          }
        } )
        .catch( error => {
          displayAuthSendError( error );
          console.error( 'Error:', error );
        } );
      displaySendStatus();
      break;
  }
}

const typeWriter = ( _ts ) => {
  if( ts !== 0 && typeBuffer !== '' && _ts - ts > ( Math.random() * 10 ) ) {
    const line = terminal.querySelector( '.line:last-child' );
    if( line.classList.contains( 'complete' ) ) {
      terminal.innerHTML += '<div class="line"></div>';
      const line = terminal.querySelector( '.line:last-child' );
    }
    if( typeBuffer[ 0 ] === '\n' ) {
      typeBuffer = typeBuffer.slice( 1 );
      line.classList.add( 'complete' );
    }
    else if( typeBuffer[ 0 ] === '#' ) {
      typeBuffer = typeBuffer.slice( 1 );
      terminal.classList.add( 'interactive' );
    }
    else if( typeBuffer[ 0 ] === '*' ) {
      typeBuffer = typeBuffer.slice( 1 );
      line.classList.add( 'complete' );
      terminal.innerHTML += `<a href=\"/ssid/${itemId++}\" class=\"line listitem\"></a>`;
    }
    else if( typeBuffer[ 0 ] === '$' ) {
      typeBuffer = typeBuffer.slice( 1 );
      line.classList.add( 'clickable' );
      if( typeBuffer[ 0 ] === 'r' ) {
        line.classList.add( 'refresh' );
        typeBuffer = typeBuffer.slice( 1 );
      }
    }
    else if( typeBuffer[ 0 ] === '€' ) {
      typeBuffer = typeBuffer.slice( 1 );
      line.classList.add( 'emphasized' );
    }
    else if( typeBuffer[ 0 ] === '§' ) {
      typeBuffer = typeBuffer.slice( 1 );
      line.classList.add( 'complete' );
      terminal.innerHTML += '<div class="line prompt" contenteditable="true"></div>';
      terminal.querySelector( '.line:last-child' ).focus();
      document.querySelector( '.line.prompt' ).addEventListener( 'keydown', handleUserInput );
    }
    else {
      line.innerHTML += typeBuffer[ 0 ];
      typeBuffer = typeBuffer.slice( 1 );
      if( typeBuffer === '' ) {
        line.classList.add( 'complete' );
      }
    }
    document.querySelectorAll( '.listitem' ).forEach( ( item, i ) => {
      item.addEventListener( 'click', ( e ) => {
        onSSIDSelect( i, e.target.innerHTML.trim() );
        e.preventDefault();  
      } );
    } );
    document.querySelectorAll( '.clickable.refresh' ).forEach( ( item, i ) => {
      item.addEventListener( 'click', ( e ) => {
        window.location.reload();
        e.preventDefault();  
      } );
    } );
  }
  ts = _ts;
  if( typeBuffer !== '' ) {
    window.requestAnimationFrame( typeWriter );
  }
}

const clearTerminal = () => {
  terminal.innerHTML = '<div class="line"></div>';
}

const displaySSIDList = ( ssidList ) => {
  clearTerminal();
  typeBuffer = `Velkommen!\n Velg ditt hjemmenettverk:\n${ssidList}\n\n\n $rLast inn på nytt\n \n espen50> `;
  window.requestAnimationFrame( typeWriter );
}

const promptSSIDPassword = () => {
  clearTerminal();
  typeBuffer = `$r< Tilbake\n \n Passord for\n \n €${ssid}\n \n §`;
  window.requestAnimationFrame( typeWriter );
}

const displaySendStatus = () => {
  clearTerminal();
  typeBuffer = `€Passord lagret!\n \n Følg videre instruksjoner\n på OLED-displayet\n Du kan lukke dette vinduet.\n \n `;
  window.requestAnimationFrame( typeWriter );
}

const displayAuthSendOK = () => {
  clearTerminal();
  typeBuffer = `€Passord lagret!\n \n Følg videre instruksjoner\n på OLED-displayet\n \n `;
  window.requestAnimationFrame( typeWriter );
}

const displayAuthSendError = ( msg ) => {
  clearTerminal();
  if( msg ) {
    typeBuffer = `°En feil har oppstått!\n ${msg}\n \n Prøv igjen!\n \n `;
  }
  else {
    typeBuffer = `°En feil har oppstått!\n \n Prøv igjen!\n \n `;
  }
  window.requestAnimationFrame( typeWriter );
}
