task main() {

	datalogClear();

	while(true) {
		// Keep the program alive.

		datalogDataGroupStart();
		datalogAddValue( 0, sinDegrees(nSysTime) * 100);
		datalogDataGroupEnd();

		delay(20);
	}
}
