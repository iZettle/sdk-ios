//
//  NSString+URLEncoding.h
//  iZettle
//
//  Created by Jens Utbult on 2010-10-21.
//  Copyright 2010 iZettle AB. All rights reserved.
//


@import Foundation;


@interface  NSString (URLEncoding)

/// Returns the character set for characters allowed in the individual parameters within a query URL component.
///
/// The query component of a URL is the component immediately following a question mark (?).
/// For example, in the URL `http://www.example.com/index.php?key1=value1#jumpLink`, the query
/// component is `key1=value1`. The individual parameters of that query would be the key `key1`
/// and its associated value `value1`.
///
/// According to RFC 3986, the set of unreserved characters includes
///
/// `ALPHA / DIGIT / "-" / "." / "_" / "~"`
///
/// In section 3.4 of the RFC, it further recommends adding `/` and `?` to the list of unescaped characters
/// for the sake of compatibility with some erroneous implementations, so this routine also allows those
/// to pass unescaped.
- (NSString *)encodePercentEscapesPerRFC3986;

- (NSString *)encodePercentEscapesPerRFC2396;

- (NSString *)decodeAllPercentEscapes;
// I did an experiment to find out which ASCII characters are encoded,
// by encoding a string with all the nonalphanumeric characters available on the
// Macintosh keyboard, with and without the shift key down. There were fourteen:
// ` # % ^ [ ] { } \ | " < >
// You only see thirteen because the fourtheenth one is the space character, " ".
// This agrees with the lists of "space" "delims" and "unwise" in by RFC 2396 sec. 2.4.3
// Also, I found that all of the non-ASCII characters available on the Macintosh
// keyboard by using option or shift+option are also encoded. Some of these have
// two bytes of unicode to encode, for example %C2%A4 for 0xC2A4

@end
