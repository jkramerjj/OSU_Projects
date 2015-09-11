/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


import java.io.Writer;

import junit.framework.TestCase;

import org.junit.Assert;



/**
 * Performs Validation Test for url validations.
 *
 * @version $Revision: 1128446 $ $Date: 2011-05-27 13:29:27 -0700 (Fri, 27 May 2011) $
 */
public class UrlValidatorTest extends TestCase {
    
    private boolean printStatus = false;
    private boolean printIndex = false;//print index that indicates current scheme,host,port,path, query test were using.
    
    public UrlValidatorTest(String testName) {
        super(testName);
    }
    
    
    
    public void testManualTest()
    {
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
        System.out.println(urlVal.isValid("http://www.amazon.com"));
        Assert.assertEquals(true, urlVal.isValid("http:://www.amazon.com?book=buyIt"));
        Assert.assertEquals(false, urlVal.isValid("zgtdp:://www.amazon.com"));
        Assert.assertEquals(true, urlVal.isValid("htp://www.amazon.com"));
        Assert.assertEquals(true, urlVal.isValid("ftp://www.amazon.com"));
        Assert.assertEquals(false, urlVal.isValid("http://www.amazon.c0m"));
        Assert.assertEquals(false, urlVal.isValid("http:/www.amazon.com"));
        Assert.assertEquals(false, urlVal.isValid("http//www.amazon.com"));
        Assert.assertEquals(false, urlVal.isValid("192.256.23.41"));
        Assert.assertEquals(false, urlVal.isValid("192..25.23.41"));
        Assert.assertEquals(false, urlVal.isValid("htp:www.amazon.com"));
        Assert.assertEquals(false, urlVal.isValid("ftp:www.amazon.com"));
        Assert.assertEquals(false, urlVal.isValid("m"));
        Assert.assertEquals(false, urlVal.isValid(""));
        Assert.assertEquals(false, urlVal.isValid(" "));
        
        
        
    }
    
    public void testYourFirstPartition() {
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
        
        Assert.assertEquals(true, urlVal.isValid("http://google.com"));
        Assert.assertEquals(true, urlVal.isValid("fttp://google.com"));
        Assert.assertEquals(true, urlVal.isValid("h3t://google.com"));
        Assert.assertEquals(false, urlVal.isValid("3ht://google.com"));
        Assert.assertEquals(false, urlVal.isValid("http:/google.com"));
        Assert.assertEquals(false, urlVal.isValid("http:google.com"));
        Assert.assertEquals(false, urlVal.isValid("http/google.com"));
        Assert.assertEquals(false, urlVal.isValid("://google.com"));
        
    }
    
    public void testYourSecondPartition() {
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
        Assert.assertEquals(true, urlVal.isValid("http://www.google.com"));
        Assert.assertEquals(true, urlVal.isValid("http://go.com"));
        Assert.assertEquals(true, urlVal.isValid("http://go.au"));
        Assert.assertEquals(true, urlVal.isValid("http://0.0.0.0"));
        Assert.assertEquals(true, urlVal.isValid("http://255.255.255.255"));
        Assert.assertEquals(false, urlVal.isValid("http://256.256.256.256"));
        Assert.assertEquals(true, urlVal.isValid("http://255.com"));
        Assert.assertEquals(false, urlVal.isValid("http://1.2.3.4.5"));
        Assert.assertEquals(false, urlVal.isValid("http://go.a"));
        Assert.assertEquals(false, urlVal.isValid("http://go.ala"));
        Assert.assertEquals(true, urlVal.isValid("http://go.cc"));
        Assert.assertEquals(false, urlVal.isValid("http://go.1aa"));
        Assert.assertEquals(false, urlVal.isValid("http://"));
    }
    
    public void testYourThridPartition() {
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
        Assert.assertEquals(true, urlVal.isValid("http://www.google.com:80"));
        Assert.assertEquals(true, urlVal.isValid("http://www.google.com:65535"));
        Assert.assertEquals(true, urlVal.isValid("http://www.google.com:0"));
        Assert.assertEquals(true, urlVal.isValid("http://www.google.com"));
        Assert.assertEquals(false, urlVal.isValid("http://www.google.com:-1"));
        Assert.assertEquals(true, urlVal.isValid("http://www.google.com:65636"));
        Assert.assertEquals(false, urlVal.isValid("http://www.google.com:65a"));
    }
    
    public void testYourFourthPartition() {
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
        Assert.assertEquals(true, urlVal.isValid("http://www.google.com/tests1"));
        Assert.assertEquals(true, urlVal.isValid("http://www.google.com/t123"));
        Assert.assertEquals(true, urlVal.isValid("http://www.google.com/$23"));
        Assert.assertEquals(false, urlVal.isValid("http://www.google.com/.."));
        Assert.assertEquals(false, urlVal.isValid("http://www.google.com/../"));
        Assert.assertEquals(true, urlVal.isValid("http://www.google.com/test1/"));
        Assert.assertEquals(true, urlVal.isValid("http://www.google.com"));
        Assert.assertEquals(true, urlVal.isValid("http://www.google.com/test1/file"));
        Assert.assertEquals(false, urlVal.isValid("http://www.google.com/..//file"));
        Assert.assertEquals(false, urlVal.isValid("http://www.google.com/test1//file"));
        
    }
    
    public void testYourFifthPartition() {
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
        Assert.assertEquals(true, urlVal.isValid("http://www.google.com/tests1/"));
        Assert.assertEquals(true, urlVal.isValid("http://www.google.com/tests1/file"));
        Assert.assertEquals(true, urlVal.isValid("http://www.google.com/t123/file"));
        Assert.assertEquals(true, urlVal.isValid("http://www.google.com/$23/file"));
        Assert.assertEquals(false, urlVal.isValid("http://www.google.com/../file"));
        Assert.assertEquals(false, urlVal.isValid("http://www.google.com/..//file"));
    }
    
    public void testYourSixthPartition() {
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
        Assert.assertEquals(true, urlVal.isValid("http://www.google.com?action=view"));
        Assert.assertEquals(true, urlVal.isValid("http://www.google.com?action=edit&mode=up"));
        Assert.assertEquals(true, urlVal.isValid("http://www.google.com"));
        
    }
    
    public void testYourSeventhPartition() {
        UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
        Assert.assertEquals(true, urlVal.isValid("http://www.google.com"));
        
    }
    
    
    
    public void testIsValid()
    {
        for(int i = 0;i<10000;i++)
        {
            
        }
    }
    
    public void testUrl()
    {
        
        long options =
        UrlValidator.ALLOW_2_SLASHES
        + UrlValidator.ALLOW_ALL_SCHEMES
        + UrlValidator.NO_FRAGMENTS;
        UrlValidator urlVal = new UrlValidator(null, null, options);
        ///if(urlVal.isValid("htp://www.google.com")) { //used for testing individual urls
        // System.out.print("Error");
        //}
        for(int schemaIndex = 0; schemaIndex < testSchema.length; schemaIndex++) {
            for(int hostIndex = 0; hostIndex < testHost.length; hostIndex++) {
                for(int portIndex = 0; portIndex < testPort.length; portIndex++) {
                    for(int pathIndex = 0; pathIndex < testPath.length; pathIndex++) {
                        for(int queryIndex = 0; queryIndex < testQuery.length; queryIndex++) {
                            StringBuffer testUrl = new StringBuffer();
                            boolean expected = testSchema[schemaIndex].valid &&
                            testHost[hostIndex].valid &&
                            testPort[portIndex].valid &&
                            testPath[pathIndex].valid &&
                            testQuery[queryIndex].valid;
                            testUrl.append(testSchema[schemaIndex].item);
                            testUrl.append(testHost[hostIndex].item);
                            testUrl.append(testPort[portIndex].item);
                            testUrl.append(testPath[pathIndex].item);
                            testUrl.append(testQuery[queryIndex].item);
                            boolean result = urlVal.isValid(testUrl.toString());
                            
                            if(expected != result) {
                                System.out.print(testUrl.toString());
                                System.out.print(": FAILED");
                                System.out.println();
                            } else {
                                //System.out.print(": Passed")
                            }
                            
                        }
                        
                    }
                }
            }
        }
    }
    /**
     * Create set of tests by taking the testUrlXXX arrays and
     * running through all possible permutations of their combinations.
     *
     * @param testObjects Used to create a url.
     */
    
    public void testSchema()
    {
        long options =
        UrlValidator.ALLOW_2_SLASHES
        + UrlValidator.ALLOW_ALL_SCHEMES
        + UrlValidator.NO_FRAGMENTS;
        UrlValidator urlVal = new UrlValidator(null, null, options);
        assertTrue(urlVal.isValid("http://www.google.com"));
        for(int schemaIndex = 0; schemaIndex < testSchema.length; schemaIndex++) {
            StringBuffer testUrl = new StringBuffer();
            boolean expected = testSchema[schemaIndex].valid;
            testUrl.append(testSchema[schemaIndex].item);
            testUrl.append("www.google.com");
            boolean result = urlVal.isValid(testUrl.toString());
            if(expected != result) {
                System.out.print(testUrl.toString());
                System.out.print(": FAILED");
                System.out.println();
            }
        }
    }
    
    public void testUserInfo()
    {
        long options =
        UrlValidator.ALLOW_2_SLASHES
        + UrlValidator.ALLOW_ALL_SCHEMES
        + UrlValidator.NO_FRAGMENTS;
        UrlValidator urlVal = new UrlValidator(null, null, options);
        assertTrue(urlVal.isValid("http://www.google.com"));
        for(int userInfoIndex = 0; userInfoIndex < testUserInfo.length; userInfoIndex++) {
            StringBuffer testUrl = new StringBuffer();
            boolean expected = testUserInfo[userInfoIndex].valid;
            testUrl.append("http://");
            testUrl.append(testUserInfo[userInfoIndex].item);
            testUrl.append("www.google.com");
            boolean result = urlVal.isValid(testUrl.toString());
            if(expected != result) {
                System.out.print(testUrl.toString());
                System.out.print(": FAILED");
                System.out.println();
            }
        }
    }
    
    public void testHost()
    {
        long options =
        UrlValidator.ALLOW_2_SLASHES
        + UrlValidator.ALLOW_ALL_SCHEMES
        + UrlValidator.NO_FRAGMENTS;
        UrlValidator urlVal = new UrlValidator(null, null, options);
        assertTrue(urlVal.isValid("http://www.google.com"));
        for(int hostIndex = 0; hostIndex < testHost.length; hostIndex++) {
            StringBuffer testUrl = new StringBuffer();
            boolean expected = testHost[hostIndex].valid;
            testUrl.append("http://");
            testUrl.append(testHost[hostIndex].item);
            String test_url = testUrl.toString();
            boolean result = urlVal.isValid(testUrl.toString());
            //assertTrue(result == expected);
            if(expected != result) {
                System.out.print(testUrl.toString());
                System.out.print(": FAILED");
                System.out.println();
            }
        }
    }
    
    public void testPort()
    {
        long options =
        UrlValidator.ALLOW_2_SLASHES
        + UrlValidator.ALLOW_ALL_SCHEMES
        + UrlValidator.NO_FRAGMENTS;
        UrlValidator urlVal = new UrlValidator(null, null, options);
        assertTrue(urlVal.isValid("http://www.google.com"));
        for(int portIndex = 0; portIndex < testPort.length; portIndex++) {
            StringBuffer testUrl = new StringBuffer();
            boolean expected = testPort[portIndex].valid;
            testUrl.append("http://www.google.com");
            testUrl.append(testPort[portIndex].item);
            String string_url = testUrl.toString();
            boolean result = urlVal.isValid(string_url);
            //assertTrue(result == expected);
            if(expected != result) {
                System.out.print(testUrl.toString());
                System.out.print(": FAILED");
                System.out.println();
            }
        }
    }
    
    public void testPath()
    {
        long options =
        UrlValidator.ALLOW_2_SLASHES
        + UrlValidator.ALLOW_ALL_SCHEMES
        + UrlValidator.NO_FRAGMENTS;
        UrlValidator urlVal = new UrlValidator(null, null, options);
        assertTrue(urlVal.isValid("http://www.google.com"));
        for(int pathIndex = 0; pathIndex < testPath.length; pathIndex++) {
            StringBuffer testUrl = new StringBuffer();
            boolean expected = testPath[pathIndex].valid;
            testUrl.append("http://www.google.com");
            testUrl.append(testPath[pathIndex].item);
            boolean result = urlVal.isValid(testUrl.toString());
            if(expected != result) {
                System.out.print(testUrl.toString());
                System.out.print(": FAILED");
                System.out.println();
            }
        }
    }
    
    public void testQuery()
    {
        long options =
        UrlValidator.ALLOW_2_SLASHES
        + UrlValidator.ALLOW_ALL_SCHEMES
        + UrlValidator.NO_FRAGMENTS;
        UrlValidator urlVal = new UrlValidator(null, null, options);
        assertTrue(urlVal.isValid("http://www.google.com"));
        for(int portQuery = 0; portQuery < testQuery.length; portQuery++) {
            StringBuffer testUrl = new StringBuffer();
            boolean expected = testQuery[portQuery].valid;
            testUrl.append("http://www.google.com");
            testUrl.append(testQuery[portQuery].item);
            boolean result = urlVal.isValid(testUrl.toString());
            if(expected != result) {
                System.out.print(testUrl.toString());
                System.out.print(": FAILED");
                System.out.println();
            }
        }
    }
    
    ResultPair[] testSchema = {new ResultPair("about://",true),
    new ResultPair("crid://", true),
    new ResultPair("http://", true),
    new ResultPair("https://", true),
    new ResultPair("gopher://", true),
    new ResultPair("tel://", true),
    new ResultPair("telnet://", true),
    new ResultPair("tv://", true),
    new ResultPair("sms://", true),
    new ResultPair("1h://", false),
    new ResultPair("h1://", true),
    new ResultPair("https//", false),
    new ResultPair("https:/", false),
    new ResultPair("https:", false),
    new ResultPair("z39.50s://", true)
    };
    
    ResultPair[] testUserInfo = {new ResultPair("", true),
    new ResultPair("frank:secret@", true),
    new ResultPair("frank:secret", false),
    new ResultPair("frank@secret@", false)
    };
    
    ResultPair[] testHost = {new ResultPair("", false),
    new ResultPair("www.google.com", true),
    new ResultPair("google.com", true),
    new ResultPair("www.google", false),
    new ResultPair("test.edu", true),
    new ResultPair("test.co.uk", true),
    new ResultPair("test.fr", true),
    new ResultPair("test.org", true),
    new ResultPair("test.net", true),
    new ResultPair("test.gov", true),
    new ResultPair("test.mil", true),
    new ResultPair("test.al", true),
    new ResultPair("test.ro", true),
    new ResultPair("test.ac.uk", true),
    new ResultPair("test.gov.uk", true),
    new ResultPair("5.24.111.0", true),
    new ResultPair("1.1", false),
    new ResultPair("256.256.256.256", false),
    new ResultPair("255.255.255.255", true),
    new ResultPair(".1.2.3.4.", false),
    new ResultPair("255.com", true),
    new ResultPair("www.borough.shippensburg.pa.us", true), //added for narrowing down the issues
    new ResultPair("www.test.ro", true), //added for narrowing down the issues
    new ResultPair("www.test.test.com", true) //added for narrowing down the issues
    };
    
    ResultPair[] testPort = {new ResultPair("", true),
    new ResultPair(":80", true),
    new ResultPair(":2342", true),
    new ResultPair(":11", true), //added for narrowing down the issues
    new ResultPair(":111", true), //added for narrowing down the issues
    new ResultPair(":1111", true), //added for narrowing down the issues
    new ResultPair(":11111", true), //added for narrowing down the issues
    new ResultPair(":111111", false), //added for narrowing down the issues
    new ResultPair("80:", false),
    new ResultPair(":a1234", false),
    new ResultPair(":-987", false),
    new ResultPair(":1", true)
    };
    
    ResultPair[] testPath = {new ResultPair("", true),
    new ResultPair("/test/", true),
    new ResultPair("/test", true),
    new ResultPair("/test//", true),
    new ResultPair("/test/test1/", true),
    new ResultPair("/test//test1/", true),
    new ResultPair("/2343/", true),
    new ResultPair("/2342", true),
    new ResultPair("test", false),
    new ResultPair("//test", true),
    new ResultPair("/ / /", false),
    new ResultPair("/$test", true)
    };
    
    ResultPair[] testQuery = {new ResultPair("", true),
    new ResultPair("?test=true", true),
    new ResultPair("?test=true&test1=false", true),
    new ResultPair("?test=true;test1=true", true),
    new ResultPair("?test=true test1=false", false)
    };
}
