from sklearn.preprocessing import StandardScaler, MinMaxScaler
class df_preparation:
    def __init__(self, training_df, df):
        self.training_df = training_df
        self.df = df

    def change_numeric_features(self):
        def change_blood_type():
            self.df['A'] = self.df["blood_type"].isin(["A+", "A-"]).apply(lambda x: int(x))
            self.df['A'] = self.df["blood_type"].isin(["A+", "A-"]).apply(lambda x: int(x))
            self.df['B'] = self.df["blood_type"].isin(["B+", "B-", "AB+", "AB-"]).apply(lambda x: int(x))
            self.df['O'] = self.df["blood_type"].isin(["O+", "O-"]).apply(lambda x: int(x))
            self.df.drop('blood_type', axis=1, inplace=True)

        def change_current_location():
            self.df["current_location_x"] = self.df["current_location"].apply(lambda x: (x.split(","))[0][2:-1]).astype(
                float)
            self.df["current_location_y"] = self.df["current_location"].apply(lambda x: (x.split(","))[1][2:-2]).astype(
                float)
            self.training_df["current_location_x"] = self.training_df["current_location"].apply(
                lambda x: (x.split(","))[0][2:-1]).astype(
                float)
            self.training_df["current_location_y"] = self.training_df["current_location"].apply(
                lambda x: (x.split(","))[1][2:-2]).astype(
                float)
            self.df.drop('current_location', axis=1, inplace=True)

        change_current_location()
        change_blood_type()

    def change_categorical_features(self):
        def change_symptoms():
            self.df["low_appetite"] = self.df["symptoms"].str.contains("low_appetite").fillna(value=False).apply(
                lambda x: int(x))
            self.df["cough"] = self.df["symptoms"].str.contains("cough").fillna(value=False).apply(lambda x: int(x))
            self.df["shortness_of_breath"] = self.df["symptoms"].str.contains("shortness_of_breath").fillna(
                value=False).apply(lambda x: int(x))
            self.df["fever"] = self.df["symptoms"].str.contains("fever").fillna(value=False).apply(lambda x: int(x))
            self.df["sore_throat"] = self.df["symptoms"].str.contains("sore_throat").fillna(value=False).apply(
                lambda x: int(x))

            self.df.drop('symptoms', axis=1, inplace=True)

        def change_sex():
            self.df.sex = self.df.sex.replace(to_replace='F', value=-1)
            self.df.sex = self.df.sex.replace(to_replace='M', value=1)

        change_sex()
        change_symptoms()

    def feature_manipulation(self):
        self.df.drop(['pcr_date', 'patient_id'], axis=1, inplace=True)
        for i in ['A', 'B', 'O', 'cough', 'low_appetite', 'shortness_of_breath', 'sore_throat', 'fever']:
            self.df[i] = self.df[i].replace(to_replace=0, value=-1)

    def normalization(self):
        def stdNormal(feature):
            df = self.df[[feature]]
            scaler = StandardScaler()
            scaler.fit(self.training_df[[feature]])  # scaling on training!
            normalaized_feature = scaler.transform(df)
            self.df[feature] = normalaized_feature

        def minMaxNormal(feature):
            df = self.df[[feature]]
            scaler = MinMaxScaler((-1, 1))
            scaler.fit(self.training_df[[feature]])  # scaling on training!
            normalaized_feature = scaler.transform(df)
            self.df[feature] = normalaized_feature

        min_max_features = ['age', 'PCR_03', 'PCR_04', 'PCR_05', 'happiness_score', 'conversations_per_day',
                            'sport_activity', 'PCR_01', 'PCR_02', 'PCR_07', 'PCR_09', 'current_location_y',
                            'num_of_siblings']
        std_features = ['weight', 'sugar_levels', 'household_income', 'PCR_06', 'PCR_08', 'PCR_10',
                        'current_location_x']

        for feature in std_features:
            stdNormal(feature)

        for feature in min_max_features:
            minMaxNormal(feature)


def prepare_data(training_df, new_data):
    new_data_return = df_preparation(training_df.copy(), new_data.copy())
    new_data_return.change_categorical_features()
    new_data_return.change_numeric_features()
    new_data_return.feature_manipulation()
    new_data_return.normalization()

    return new_data_return.df