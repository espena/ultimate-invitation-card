<?php

  $src = $argv[ 1 ];
  $dst = $argv[ 2 ];

  if( !file_exists( $src ) )
  {
    echo "File not found: $src\n";
    exit( 1 );
  }

  if( file_exists( $dst ) )
  {
    unlink( $dst );
  }

  $data = file_get_contents( $src );

  $prologue = <<<EOT
#ifndef __html_captive_portal_hpp__
#define __html_captive_portal_hpp__

  namespace espena::components::html {
      
    const char captive_portal[] = {

EOT;

  $epilogue = <<<EOT
    
  } // namespace espena::components::html

#endif // __html_captive_portal_hpp__
EOT;

  $byteArray = [ ];

  for( $i = 0; $i < strlen( $data ); $i++ )
  {
    $byte = ord( $data[ $i ] );
    array_push( $byteArray, sprintf( "0x%02X", $byte ) );
    array_push( $byteArray, $i % 16 == 15 ? ",\n\t\t\t" : ", " );
  }

  $bytearray = implode( "", $byteArray );
  $bytearray = "\t\t\t" . trim( $bytearray, ", \n\t" ) . "\n\t\t};\n";

  file_put_contents( $dst, "{$prologue}{$bytearray}{$epilogue}" );

  exit( 0 );

?>