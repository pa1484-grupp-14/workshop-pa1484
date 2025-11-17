A quick demo for how the API will work in the project using javascript since its easier to test.
The functions are available in API.js to use for example getStationInfo function, do the following:

line: data = await getStationInfo(stationName, typeOfData); stationName = a stations string name,  typeOfData = 1, 2, 3, 4 etc(gives storm, rain temperature and so fourth)


To play with the API:
1. Right click on html file and click on reveal in file explorer, then click on html file.
2. Right click and click on inspect, Click on console.
3. write the code in "Line" above, with any function you want.

API Structure exlaination 
https://opendata-download-metobs.smhi.se/api/version/{version}/parameter/{parameter}/station/{station}/period/{period}/data.json  
version - version of the api for example, 2.0, 1.0 or latest
parameter - 1, 2 ,3, 4, 5, 6, 7, 8, 9, 10, check available paramters at: https://opendata-download-metobs.smhi.se/metobs/resources/parameter 
station - key, every station is associated via name and key. Search up smhi station for karlskrona and see what station "key" it has in: https://opendata-download-metobs.smhi.se/api/version/{version}/parameter/{parameter}.json
          obs! Dont forget to intent for readabillity and search for attribute "key" corresponding to name.
period - latest-months, latests-days etc. https://opendata-download-metobs.smhi.se/metobs/resources/period
